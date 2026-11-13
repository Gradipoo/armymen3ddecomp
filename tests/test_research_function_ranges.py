# SPDX-License-Identifier: GPL-3.0-or-later

import hashlib
import importlib.util
import io
import json
import struct
import sys
import tempfile
import unittest
from contextlib import redirect_stderr, redirect_stdout
from pathlib import Path
from unittest.mock import patch

TOOLS = Path(__file__).resolve().parents[1] / 'tools'
sys.path.insert(0, str(TOOLS))
try:
    SPEC = importlib.util.spec_from_file_location('research_function_ranges', TOOLS / 'research_function_ranges.py')
    RANGES = importlib.util.module_from_spec(SPEC)
    SPEC.loader.exec_module(RANGES)
finally:
    sys.path.remove(str(TOOLS))

LOAD = 0x80010000
TEXT = bytes(64)
EXE = bytearray(0x800) + TEXT
EXE[:8] = b'PS-X EXE'
struct.pack_into('<II', EXE, 0x18, LOAD, len(TEXT))
INVENTORY = b'address\tsize\tname\n80010000\t16\ta\n80010010\t16\tb\n'


def row(start, name, ranges=None, size=16):
    return {'address': f'0x{start:08x}', 'name': name, 'size': size,
            'ranges': ranges if ranges is not None else [
                {'space': 'ram', 'start': f'0x{start:08x}', 'end': f'0x{start + size - 1:08x}'}]}


def metadata():
    return {'schema_version': 1, 'language_id': 'MIPS:LE:32:default',
            'default_address_space': 'ram', 'source_image_sha256': hashlib.sha256(TEXT).hexdigest(),
            'ghidra_version': 'synthetic', 'functions': [row(LOAD, 'a'), row(LOAD + 16, 'b')]}


class RangeTests(unittest.TestCase):
    def test_contiguous_metadata_is_only_a_boundary_lead(self):
        result = RANGES.validate(metadata(), INVENTORY, bytes(EXE))
        self.assertEqual(result['eligible_contiguous_windows'], 2)
        self.assertTrue(result['inventory_consistent'])
        self.assertIn('not prove', result['warning'])
        self.assertIn('not current memory', result['warning'])

    def test_same_body_count_can_hide_discontiguous_ranges(self):
        data = metadata()
        data['functions'][0]['ranges'] = [
            {'space': 'ram', 'start': '0x80010000', 'end': '0x80010007'},
            {'space': 'ram', 'start': '0x80010028', 'end': '0x8001002f'}]
        result = RANGES.validate(data, INVENTORY, bytes(EXE))
        self.assertEqual(result['discontiguous_bodies'], 1)
        self.assertEqual(result['eligible_contiguous_windows'], 1)
        self.assertTrue(result['inventory_consistent'])

    def test_overlapping_functions_are_ineligible(self):
        data = metadata()
        data['functions'][0]['ranges'][0]['end'] = '0x80010017'
        data['functions'][0]['size'] = 24
        result = RANGES.validate(data, INVENTORY, bytes(EXE))
        self.assertEqual(result['overlapping_bodies'], 2)
        self.assertEqual(result['eligible_contiguous_windows'], 0)
        self.assertFalse(result['inventory_consistent'])

    def test_missing_extra_or_renamed_inventory_is_reported(self):
        data = metadata()
        data['functions'] = [row(LOAD + 16, 'renamed'), row(LOAD + 32, 'extra')]
        result = RANGES.validate(data, INVENTORY, bytes(EXE))
        self.assertFalse(result['inventory_consistent'])
        self.assertEqual(result['missing_inventory_entries'], ['0x80010000'])
        self.assertEqual(len(result['inconsistent_entries']), 2)

    def test_wrong_source_image_or_language_fails(self):
        for field, value in [('source_image_sha256', '0' * 64), ('source_image_sha256', None),
                             ('language_id', 'MIPS:BE:32:default'), ('schema_version', True)]:
            data = metadata()
            data[field] = value
            with self.subTest(field=field, value=value), self.assertRaises(ValueError):
                RANGES.validate(data, INVENTORY, bytes(EXE))

    def test_invalid_range_metadata_fails(self):
        changes = [
            lambda r: r.update(size=15),
            lambda r: r.update(address='0x80010020'),
            lambda r: r['ranges'][0].update(start='0x80010010'),
            lambda r: r.update(ranges=r['ranges'] * 2),
            lambda r: r.update(address='80010000'),
            lambda r: r['ranges'][0].update(space='other'),
        ]
        for mutate in changes:
            data = metadata()
            mutate(data['functions'][0])
            with self.subTest(data=data), self.assertRaises(ValueError):
                RANGES.validate(data, INVENTORY, bytes(EXE))

    def test_default_space_ranges_outside_exe_are_ineligible(self):
        data = metadata()
        data['functions'].append(row(LOAD + 64, 'past'))
        result = RANGES.validate(data, INVENTORY, bytes(EXE))
        self.assertIn('body outside EXE text', result['functions'][-1]['reasons'])
        self.assertFalse(result['functions'][-1]['eligible_contiguous_window'])

    def test_cli_nonzero_for_inventory_conflict_and_failed_rerun_clears_report(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            (root / 'build').mkdir()
            source = root / 'metadata.json'
            target = root / 'exe'
            table = root / 'inventory.tsv'
            out = root / 'build' / 'report.json'
            data = metadata()
            data['functions'][0]['name'] = 'renamed'
            source.write_text(json.dumps(data))
            target.write_bytes(EXE)
            table.write_bytes(INVENTORY)
            args = [str(source), str(target), '--inventory', str(table), '--out', str(out)]
            with patch.dict(RANGES.local_output.__globals__, {'ROOT': root}), \
                    redirect_stdout(io.StringIO()), redirect_stderr(io.StringIO()):
                self.assertEqual(RANGES.main(args), 1)
                self.assertFalse(json.loads(out.read_text())['inventory_consistent'])
                source.write_text('broken JSON')
                self.assertEqual(RANGES.main(args), 2)
                self.assertFalse(out.exists())
                self.assertEqual(RANGES.main(args[:-1] + [str(source)]), 2)
                self.assertEqual(source.read_text(), 'broken JSON')


if __name__ == '__main__':
    unittest.main()
