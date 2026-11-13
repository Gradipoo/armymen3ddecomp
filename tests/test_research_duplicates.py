# SPDX-License-Identifier: GPL-3.0-or-later
"""Synthetic cases for duplicate leads and their boundary/privacy limits."""

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


SPEC = importlib.util.spec_from_file_location(
    'research_duplicates', Path(__file__).resolve().parents[1] / 'tools/research_duplicates.py')
DUP = importlib.util.module_from_spec(SPEC)
sys.modules[SPEC.name] = DUP
SPEC.loader.exec_module(DUP)
LOAD = 0x80010000


def exe(text):
    result = bytearray(0x800) + text
    result[:8] = b'PS-X EXE'
    struct.pack_into('<II', result, 0x18, LOAD, len(text))
    return bytes(result)


def inventory(*rows):
    return ('address\tsize\tname\n' + ''.join(
        f'{address:08x}\t{size}\t{name}\n' for address, size, name in rows)).encode()


class DuplicateTests(unittest.TestCase):
    def test_exact_bytes_only_with_size_and_pc_relative_caveat(self):
        blob = bytes(range(16))
        text = blob + blob + bytes(reversed(blob))
        rows = DUP.read_inventory(inventory(
            (LOAD, 16, 'a'), (LOAD + 16, 16, 'b'), (LOAD + 32, 16, 'c')))
        report = DUP.duplicate_leads(LOAD, text, rows, 16)
        self.assertEqual(len(report['groups']), 1)
        self.assertEqual([e['name'] for e in report['groups'][0]['members']], ['a', 'b'])
        self.assertEqual(report['boundary_status'], 'unreviewed')
        self.assertIn('PC-relative', report['warning'])
        self.assertNotIn('bytes', report['groups'][0])

    def test_all_overlapping_ranges_excluded_including_nested_ranges(self):
        rows = [DUP.Entry(LOAD, 40, 'outer'), DUP.Entry(LOAD + 4, 8, 'nested'),
                DUP.Entry(LOAD + 16, 8, 'later'), DUP.Entry(LOAD + 40, 8, 'adjacent')]
        report = DUP.duplicate_leads(LOAD, bytes(48), rows, 8)
        self.assertEqual(report['groups'], [])
        self.assertEqual(len(report['excluded']), 3)
        self.assertEqual(report['considered_entries'], 1)
        self.assertTrue(all('overlapping' in e['reasons'][0] for e in report['excluded']))

    def test_small_and_out_of_range_entries_excluded(self):
        rows = [DUP.Entry(LOAD - 4, 16, 'before'), DUP.Entry(LOAD, 4, 'small'),
                DUP.Entry(LOAD + 16, 16, 'after')]
        report = DUP.duplicate_leads(LOAD, bytes(16), rows, 8)
        self.assertEqual(report['considered_entries'], 0)
        self.assertEqual(len(report['excluded']), 3)

    def test_bad_inventory_rejected(self):
        cases = [b'wrong\theader\n', inventory((LOAD, 3, 'bad')),
                 inventory((LOAD + 1, 8, 'bad')), inventory((0xfffffffc, 8, 'wrap')),
                 inventory((LOAD, 8, 'a'), (LOAD, 8, 'b')),
                 b'address\tsize\tname\n80010000\t8\n',
                 b'address\tsize\tname\n80010000\t8\ta\textra\n']
        for data in cases:
            with self.subTest(data=data), self.assertRaises(ValueError):
                DUP.read_inventory(data)

    def test_bad_exe_and_minimum_rejected(self):
        for data in (b'PS-X EXE', exe(bytearray(8))[:-1], exe(bytearray(3))):
            with self.subTest(size=len(data)), self.assertRaises(ValueError):
                DUP.read_text(data)
        with self.assertRaises(ValueError):
            DUP.duplicate_leads(LOAD, bytes(16), [], 4)

    def test_report_local_only_and_does_not_overwrite_inputs(self):
        with tempfile.TemporaryDirectory() as temporary, patch.object(DUP, 'ROOT', Path(temporary)):
            root = Path(temporary)
            target = root / 'build' / 'input'
            target.parent.mkdir()
            target.write_bytes(exe(bytearray(range(16)) * 2))
            table = root / 'inventory.tsv'
            table.write_bytes(inventory((LOAD, 16, 'a'), (LOAD + 16, 16, 'b')))
            out = root / 'build' / 'report.json'
            args = [str(target), '--inventory', str(table), '--out', str(out)]
            with redirect_stdout(io.StringIO()):
                self.assertEqual(DUP.main(args), 0)
            report = json.loads(out.read_text())
            self.assertEqual(len(report['groups']), 1)
            self.assertIn('exe_sha256', report)
            with redirect_stderr(io.StringIO()):
                self.assertEqual(DUP.main(args[:-1] + [str(root / 'public.json')]), 2)
                self.assertEqual(DUP.main(args[:-1] + [str(target)]), 2)
            self.assertFalse((root / 'public.json').exists())
            self.assertEqual(target.read_bytes()[:8], b'PS-X EXE')
            table.write_text('broken inventory')
            with redirect_stderr(io.StringIO()):
                self.assertEqual(DUP.main(args), 2)
            self.assertFalse(out.exists(), 'a failed rerun must invalidate the old report')

    def test_output_cannot_escape_build_through_symlink(self):
        with tempfile.TemporaryDirectory() as temporary, patch.object(DUP, 'ROOT', Path(temporary)):
            root = Path(temporary)
            (root / 'build').mkdir()
            (root / 'outside').mkdir()
            try:
                (root / 'build' / 'link').symlink_to(root / 'outside', target_is_directory=True)
            except OSError:
                self.skipTest('symlinks unavailable')
            with self.assertRaises(ValueError):
                DUP.local_output(root / 'build' / 'link' / 'report.json')

    def test_build_directory_itself_cannot_be_a_symlink_escape(self):
        with tempfile.TemporaryDirectory() as temporary, patch.object(DUP, 'ROOT', Path(temporary)):
            root = Path(temporary)
            (root / 'outside').mkdir()
            try:
                (root / 'build').symlink_to(root / 'outside', target_is_directory=True)
            except OSError:
                self.skipTest('symlinks unavailable')
            with self.assertRaises(ValueError):
                DUP.local_output(root / 'build' / 'report.json')


if __name__ == '__main__':
    unittest.main()
