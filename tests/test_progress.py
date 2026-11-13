# SPDX-License-Identifier: GPL-3.0-or-later

import importlib.util
import tempfile
import unittest
from pathlib import Path

SPEC = importlib.util.spec_from_file_location(
    'am3d_progress', Path(__file__).resolve().parents[1] / 'tools/progress.py')
PROGRESS = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(PROGRESS)


class ProgressTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        (self.root / PROGRESS.INVENTORY).parent.mkdir(parents=True)

    def inventory(self, text='80010000\t16\tFUN_80010000\n'):
        (self.root / PROGRESS.INVENTORY).write_text(
            'address\tsize\tname\n' + text, encoding='utf-8')

    def ledger(self, text):
        (self.root / PROGRESS.LEDGER).write_text(
            '\t'.join(PROGRESS.FIELDS) + '\n' + text, encoding='utf-8')

    def test_missing_inventory_has_no_denominator(self):
        self.assertIsNone(PROGRESS.report(self.root)['counts'])

    def test_citation_does_not_advance_status(self):
        self.inventory()
        (self.root / 'docs/research/re/note.md').write_text('80010000', encoding='utf-8')
        report = PROGRESS.report(self.root)
        self.assertEqual(report['functions'][0]['status'], 'inventoried')
        self.assertEqual(report['counts']['verified']['functions'], 0)

    def test_verified_requires_all_evidence_and_counts_bytes(self):
        self.inventory()
        for name, text in [('note.md', '0x80010000'), ('source.cpp', 'our code'),
                           ('check.md', 'Synthetic check passed.')]:
            (self.root / name).write_text(text, encoding='utf-8')
        self.ledger('0x80010000\tgame\tverified\tnote.md\tsource.cpp\tcheck.md\n')
        self.assertEqual(PROGRESS.report(self.root)['counts']['verified'],
                         {'functions': 1, 'bytes': 16})
        (self.root / 'check.md').unlink()
        with self.assertRaisesRegex(ValueError, 'evidence file missing'):
            PROGRESS.report(self.root)

    def test_rejects_false_completion_and_orphan_rows(self):
        self.inventory()
        for text, error in [
            ('80010000\tgame\timplemented\t\t\t\n', 'requires note'),
            ('80010000\tgame\tdone\t\t\t\n', 'unknown category or status'),
            ('80020000\tgame\tidentified\t\t\t\n', 'absent from inventory'),
        ]:
            with self.subTest(error=error):
                self.ledger(text)
                with self.assertRaisesRegex(ValueError, error):
                    PROGRESS.report(self.root)

    def test_rejects_duplicate_addresses_and_bad_sizes(self):
        for text, error in [
            ('80010000\t16\tone\n0x80010000\t16\ttwo\n', 'duplicate address'),
            ('80010000\t-1\tone\n', 'size must be positive'),
        ]:
            self.inventory(text)
            with self.assertRaisesRegex(ValueError, error):
                PROGRESS.report(self.root)

    def test_rejects_private_and_outside_evidence(self):
        self.inventory()
        for path in ['../outside.md', 'build/local.md']:
            self.ledger(f'80010000\tgame\tresearched\t{path}\t\t\n')
            with self.assertRaisesRegex(ValueError, 'evidence must be'):
                PROGRESS.report(self.root)

    def test_note_must_cite_function(self):
        self.inventory()
        (self.root / 'note.md').write_text('Another function.', encoding='utf-8')
        self.ledger('80010000\tgame\tresearched\tnote.md\t\t\n')
        with self.assertRaisesRegex(ValueError, 'must cite the address'):
            PROGRESS.report(self.root)


if __name__ == '__main__':
    unittest.main()
