# SPDX-License-Identifier: GPL-3.0-or-later

import importlib.util
import io
import json
import struct
import tempfile
import unittest
from contextlib import redirect_stdout, redirect_stderr
from pathlib import Path
from unittest.mock import patch

SPEC = importlib.util.spec_from_file_location(
    'am3d_compare', Path(__file__).resolve().parents[1] / 'tools/compare.py')
COMPARE = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(COMPARE)
LOAD = 0x80010000


def exe(code):
    header = bytearray(0x800)
    header[:8] = b'PS-X EXE'
    struct.pack_into('<II', header, 0x18, LOAD, len(code))
    return bytes(header) + code


def elf(code, relocation=False):
    names = b'\0.text\0.shstrtab\0.rel.text\0'
    count = 4 if relocation else 3
    headers = [tuple([0] * 10),
               (1, 1, 6, 0, 52 + count * 40, len(code), 0, 0, 4, 0),
               (7, 3, 0, 0, 52 + count * 40 + len(code), len(names), 0, 0, 1, 0)]
    if relocation:
        headers.append((17, 9, 0, 0, 52 + count * 40 + len(code) + len(names),
                        8, 0, 1, 4, 8))
    data = bytearray(52)
    data[:7] = b'\x7fELF\x01\x01\x01'
    struct.pack_into('<HHI', data, 16, 1, 8, 1)
    struct.pack_into('<I', data, 32, 52)
    struct.pack_into('<HHH', data, 46, 40, count, 2)
    return bytes(data) + b''.join(struct.pack('<10I', *h) for h in headers) + code + names + b'\0' * 8


class CompareTests(unittest.TestCase):
    def test_exact_check_does_not_mask_instruction_bits(self):
        code = bytes(range(8))
        self.assertTrue(COMPARE.compare(code, code, LOAD)['exact_match'])
        changed = code[:4] + b'\xff' + code[5:]
        report = COMPARE.compare(code, changed, LOAD)
        self.assertFalse(report['exact_match'])
        self.assertEqual(report['different_words'], 1)
        self.assertEqual(report['differences'][0]['address'], '0x80010004')
        with self.assertRaisesRegex(ValueError, 'size differs'):
            COMPARE.compare(code, code + b'\0' * 4, LOAD)

    def test_exe_ranges_and_truncation(self):
        data = exe(bytes(range(16)))
        self.assertEqual(COMPARE.reference(data, LOAD + 4, 4), bytes(range(4, 8)))
        for addr, size in [(LOAD - 4, 4), (LOAD + 16, 4), (LOAD + 1, 4),
                           (LOAD, 0), (LOAD, 3)]:
            with self.subTest(addr=addr, size=size), self.assertRaises(ValueError):
                COMPARE.reference(data, addr, size)
        with self.assertRaises(ValueError):
            COMPARE.reference(data[:-1], LOAD, 4)

    def test_elf_extraction_and_relocations(self):
        code = bytes(range(8))
        self.assertEqual(COMPARE.elf_section(elf(code), '.text'), code)
        with self.assertRaisesRegex(ValueError, 'unresolved relocations'):
            COMPARE.elf_section(elf(code, relocation=True), '.text')
        with self.assertRaises(ValueError):
            COMPARE.elf_section(elf(code), '.missing')
        bad_machine = bytearray(elf(code))
        struct.pack_into('<H', bad_machine, 18, 62)
        with self.assertRaisesRegex(ValueError, 'MIPS'):
            COMPARE.elf_section(bytes(bad_machine), '.text')
        with self.assertRaises(ValueError):
            COMPARE.elf_section(elf(code)[:60], '.text')

    def test_cli_reports_stay_local_and_fail_on_mismatch(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            target = root / 'reference'
            candidate = root / 'candidate.o'
            target.write_bytes(exe(bytes(range(8))))
            args = [str(target), str(candidate), '--address', hex(LOAD), '--size', '8']
            with patch.object(COMPARE, 'ROOT', root), redirect_stdout(io.StringIO()):
                candidate.write_bytes(elf(bytes(range(8))))
                self.assertEqual(COMPARE.main(args), 0)
                candidate.write_bytes(elf(b'\xff' * 8))
                self.assertEqual(COMPARE.main(args), 1)
                report = json.loads((root / 'build/compare/80010000.json').read_text())
                self.assertFalse(report['exact_match'])
                self.assertIn('exe_sha256', report)
                candidate.write_bytes(elf(b'\0' * 4))
                with redirect_stderr(io.StringIO()):
                    self.assertEqual(COMPARE.main(args), 2)


if __name__ == '__main__':
    unittest.main()
