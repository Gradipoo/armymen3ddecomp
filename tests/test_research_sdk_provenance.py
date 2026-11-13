# SPDX-License-Identifier: GPL-3.0-or-later
"""Original synthetic signatures only. No SDK archives or game data."""

import contextlib
import io
import json
import os
import random
import struct
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import research_sdk_provenance as PROV

SCAN = PROV.SCAN
LOAD = 0x80010000


def executable(text, load=LOAD):
    data = bytearray(0x800) + text
    data[:8] = b'PS-X EXE'
    struct.pack_into('<II', data, 0x18, load, len(text))
    return bytes(data)


def signature(pattern, labels):
    return {'sig': ' '.join('??' if byte is None else f'{byte:02x}' for byte in pattern),
            'labels': [{'name': name, 'offset': offset} for name, offset in labels]}


def write_source(directory, rows, version='100', name='fixture.json'):
    path = directory / version / name
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(rows), encoding='utf-8')
    return path


def collect(directory, text, load=LOAD, versions=None):
    paths = PROV.source_paths(directory, versions)
    records, files, skipped = PROV.load_records(directory, paths)
    hits, stats = PROV.scan_records(load, text, records)
    return records, files, skipped, hits, stats


def baseline(directory, text, load=LOAD, versions=None):
    sigs = []
    for folder in ([directory / version for version in versions] if versions else [directory]):
        sigs.extend(SCAN.load_signatures(folder))
    return ''.join(f'0x{address:08x} {name} {version}\n'
                   for address, name, version in SCAN.scan(load, text, sigs)).encode()


class ProvenanceTests(unittest.TestCase):
    def test_identity_labels_threshold_and_projection_match_production(self):
        exact = list(range(1, 9))
        scattered = [None, 21, None, 22, None, 23, None, 24,
                     None, 25, None, 26, None, 27, None, 28]
        rows = [{'name': 'synthetic BSS only'},
                signature(exact, [('Alpha', 0), ('Alias', 0), ('loc_Inner', 4),
                                  ('Past', 8), ('Before', -1)]),
                signature(exact, [('Alpha', 0)]),
                signature(scattered, [('Beta', 0), ('text_Inner', 3)]),
                signature([1, 2, 3, 4, 5, 6, 7, None], [('Weak', 0)])]
        text = bytearray([0xfe] * 64)
        text[0:8] = bytes(exact)
        text[16:24] = bytes(exact)
        text[32:48] = bytes(0xaa if byte is None else byte for byte in scattered)
        with tempfile.TemporaryDirectory() as temporary:
            directory = Path(temporary)
            for version in ('100', '200'):
                write_source(directory, rows, version)
            records, files, skipped, hits, stats = collect(directory, text)
            self.assertEqual(PROV.projection(hits), baseline(directory, text))
            self.assertEqual(len(records), 8)
            self.assertEqual(len(skipped), 2)
            self.assertEqual(stats['distinct_patterns_scanned'], 2)
            self.assertEqual(len({row['record_id'] for row in records}), 8)
            self.assertEqual(records[0]['source_record_sha256'], records[4]['source_record_sha256'])
            self.assertNotEqual(records[0]['record_id'], records[4]['record_id'])
            self.assertEqual(records[0]['location_count'], 2)
            self.assertIsNone(records[3]['location_count'])
            self.assertFalse(records[0]['labels'][3]['in_signature'])
            report = PROV.make_report(records, files, skipped, hits, stats)
            serialized = json.dumps(report)
            self.assertNotIn('"pattern":', serialized)
            self.assertNotIn('"sig":', serialized)
            self.assertNotIn(rows[1]['sig'], serialized)
            self.assertEqual(report['summary']['ambiguous_name_addresses'], 2)
            self.assertTrue(any(row['decision'] == 'internal_label_lead' for row in report['hits']))
            self.assertTrue(all('reason' in row for row in report['hits']))

    def test_requested_source_order_and_address_wrap_are_preserved(self):
        rows = [signature([0] * 8, [('Wrap', 0), ('UnalignedLabel', 3)])]
        with tempfile.TemporaryDirectory() as temporary:
            directory = Path(temporary)
            for version in ('100', '200'):
                write_source(directory, rows, version)
            result = collect(directory, bytes(16), 0xfffffff8, ['200', '100'])
            hits = result[3]
            self.assertEqual(PROV.projection(hits), baseline(directory, bytes(16), 0xfffffff8, ['200', '100']))
            self.assertEqual(hits[0]['version'], '200')
            self.assertIn('0x00000003', PROV.projection(hits).decode())
            self.assertEqual(result[0][0]['location_count'], 3)

    def test_cache_uses_full_mask_not_name_or_digest(self):
        first = signature(list(range(8)), [('Same', 0)])
        second = signature(list(range(8, 16)), [('Same', 0)])
        with tempfile.TemporaryDirectory() as temporary:
            directory = Path(temporary)
            write_source(directory, [first, second, first])
            with patch.object(PROV, 'sha', return_value='0' * 64):
                records, _, _, hits, stats = collect(directory, bytes(range(16)))
            self.assertEqual(PROV.projection(hits), baseline(directory, bytes(range(16))))
            self.assertEqual(stats['distinct_patterns_scanned'], 2)
            self.assertEqual(stats['cache_reuses'], 1)
            self.assertEqual([row['record_index'] for row in records], [0, 1, 2])

    def test_long_pattern_bounds_and_shifted_anchor_miss(self):
        rows = [signature([None] * 5 + list(range(1, 9)) + [None] * 3, [('Long', 0)])]
        with tempfile.TemporaryDirectory() as temporary:
            directory = Path(temporary)
            write_source(directory, rows)
            for text in (bytes(range(1, 9)), bytes(6) + bytes(range(1, 9)) + bytes(3),
                         bytes(5) + bytes(range(1, 9)) + bytes(3)):
                with self.subTest(size=len(text)):
                    hits = collect(directory, text)[3]
                    self.assertEqual(PROV.projection(hits), baseline(directory, text))

    def test_fixed_seed_differential_oracle(self):
        randomizer = random.Random(0x3d00491)
        with tempfile.TemporaryDirectory() as temporary:
            directory = Path(temporary)
            for case in range(100):
                text = bytearray(randomizer.randrange(16) for _ in range(randomizer.randrange(0, 129)))
                rows = []
                for index in range(10):
                    length = randomizer.randrange(0, 33)
                    pattern = [None if randomizer.random() < .35 else randomizer.randrange(16)
                               for _ in range(length)]
                    if index < 2 and len(text) >= 16:
                        start = randomizer.randrange((len(text) - 16) // 4 + 1) * 4
                        pattern = [text[start + i] if i % 2 else None for i in range(16)]
                    labels = [(f'Name_{index}', 0), ('loc_Inner', length // 2),
                              ('Past', length), ('Before', -1)]
                    rows.append(signature(pattern, labels))
                rows.append(rows[0])
                write_source(directory, rows)
                with self.subTest(case=case):
                    hits = collect(directory, text)[3]
                    self.assertEqual(PROV.projection(hits), baseline(directory, text))

    def test_invalid_sources_have_same_parser_failures(self):
        cases = ['{}', '[2]', '[{"sig": 4, "labels": []}]',
                 '[{"sig": "01", "labels": [{"name": "X", "offset": true}]}]',
                 '[{"sig": "01", "labels": 7}]', '[{"sig": "zz", "labels": []}]']
        with tempfile.TemporaryDirectory() as temporary:
            directory = Path(temporary)
            path = directory / 'bad.json'
            for body in cases:
                path.write_text(body)
                with self.subTest(body=body):
                    with self.assertRaises(SCAN.ToolError):
                        SCAN.load_signatures(directory)
                    with self.assertRaises(SCAN.ToolError):
                        PROV.load_records(directory, [path])

    def test_empty_source_and_non_signature_records_match(self):
        with tempfile.TemporaryDirectory() as temporary:
            directory = Path(temporary)
            write_source(directory, [{'other': 'original metadata'}, {'sig': ''}])
            records, files, skipped, hits, stats = collect(directory, b'')
            self.assertEqual(PROV.projection(hits), baseline(directory, b''))
            report = PROV.make_report(records, files, skipped, hits, stats)
            self.assertEqual(report['summary']['raw_hit_rows'], 0)
            self.assertEqual(len(skipped), 2)

    def test_cli_output_guards_and_failed_run_invalidation(self):
        with tempfile.TemporaryDirectory() as temporary, patch.object(PROV, 'ROOT', Path(temporary)):
            root = Path(temporary)
            source = root / 'source'
            fixture = write_source(source, [signature(list(range(8)), [('Only', 0)])])
            exe = root / 'fixture.exe'
            exe.write_bytes(executable(bytearray(range(8))))
            out = root / 'build' / 'report.json'
            args = [str(exe), str(source), '--source-revision', 'synthetic', '--out', str(out)]
            with contextlib.redirect_stdout(io.StringIO()):
                self.assertEqual(PROV.main(args), 0)
            report = json.loads(out.read_text())
            self.assertEqual(report['summary']['raw_hit_rows'], 1)
            with contextlib.redirect_stderr(io.StringIO()):
                self.assertEqual(PROV.main(args[:-1] + [str(root / 'public.json')]), 2)
                self.assertEqual(PROV.main(args[:-1] + [str(out.with_suffix('.txt'))]), 2)
                self.assertEqual(PROV.main(args[:-1] + [str(fixture)]), 2)
            self.assertFalse((root / 'public.json').exists())
            self.assertEqual(json.loads(fixture.read_text())[0]['labels'][0]['name'], 'Only')
            fixture.write_text('broken json')
            with contextlib.redirect_stderr(io.StringIO()):
                self.assertEqual(PROV.main(args), 2)
            self.assertFalse(out.exists())
            out.write_text('old report')
            with contextlib.redirect_stderr(io.StringIO()):
                self.assertEqual(PROV.main(args + ['--version', 'missing']), 2)
            self.assertFalse(out.exists())

    def test_input_collision_symlink_and_hardlink_guards(self):
        with tempfile.TemporaryDirectory() as temporary, patch.object(PROV, 'ROOT', Path(temporary)):
            root = Path(temporary)
            build = root / 'build'
            build.mkdir()
            source = root / 'source'
            fixture = write_source(source, [signature(list(range(8)), [('Only', 0)])])
            exe = build / 'input.json'
            exe.write_bytes(executable(bytearray(range(8))))
            for target in (exe, fixture):
                with self.assertRaises(ValueError):
                    PROV.output_path(target, exe, source, [fixture])
            alias = build / 'hardlink.json'
            try:
                os.link(fixture, alias)
            except OSError:
                self.skipTest('hardlinks unavailable')
            args = [str(exe), str(source), '--source-revision', 'synthetic', '--out', str(alias)]
            with contextlib.redirect_stderr(io.StringIO()):
                self.assertEqual(PROV.main(args), 2)
            self.assertTrue(alias.samefile(fixture), 'collision check must precede report invalidation')
            outside = root / 'outside'
            outside.mkdir()
            link = build / 'link'
            try:
                link.symlink_to(outside, target_is_directory=True)
            except OSError:
                self.skipTest('symlinks unavailable')
            with self.assertRaises(ValueError):
                PROV.output_path(link / 'report.json', exe, source, [fixture])

    def test_build_symlink_and_bad_version_selection_rejected(self):
        with tempfile.TemporaryDirectory() as temporary, patch.object(PROV, 'ROOT', Path(temporary)):
            root = Path(temporary)
            outside = root / 'outside'
            outside.mkdir()
            try:
                (root / 'build').symlink_to(outside, target_is_directory=True)
            except OSError:
                self.skipTest('symlinks unavailable')
            with self.assertRaises(ValueError):
                PROV.output_path(root / 'build/report.json', root / 'input', root / 'sigs', [])
            for versions in (['..'], ['../other'], [''], ['100', '100'], ['one\\two']):
                with self.subTest(versions=versions), self.assertRaises(ValueError):
                    PROV.source_paths(root, versions)


if __name__ == '__main__':
    unittest.main()
