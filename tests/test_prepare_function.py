# SPDX-License-Identifier: GPL-3.0-or-later

import argparse
import importlib.util
import json
import os
import struct
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

TOOLS = Path(__file__).resolve().parents[1] / 'tools'
sys.path.insert(0, str(TOOLS))
SPEC = importlib.util.spec_from_file_location('am3d_prepare', TOOLS / 'prepare_function.py')
PREPARE = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(PREPARE)


class PrepareTests(unittest.TestCase):
    @unittest.skipUnless(os.environ.get('AM3D_ANALYSIS_PYTHON'), 'optional local analysis environment')
    def test_real_tools_name_sdk_call_without_entering_callee(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            address = 0x80081000
            target = 0x800865c8
            # Original synthetic wrapper. The SDK target itself is zero-filled.
            words = (0x27bdffe8, 0xafbf0014,
                     (3 << 26) | ((target >> 2) & 0x03ffffff), 0x00002021,
                     0x8fbf0014, 0, 0x03e00008, 0x27bd0018)
            code = struct.pack('<8I', *words)
            data = bytearray(0x800 + 0x8000)
            data[:8] = b'PS-X EXE'
            struct.pack_into('<II', data, 0x18, address, 0x8000)
            data[0x800:0x800 + len(code)] = code
            exe = root / 'synthetic-exe'
            exe.write_bytes(data)
            llvm = os.environ.get('AM3D_LLVM_MC')
            args = argparse.Namespace(exe=exe, address=address, size=len(code),
                python=Path(os.environ['AM3D_ANALYSIS_PYTHON']).absolute(), context=None,
                llvm_mc=Path(llvm).absolute() if llvm else None)
            with patch.object(PREPARE, 'ROOT', root):
                out = PREPARE.run(args)
            record = json.loads((out / 'task.json').read_text())
            self.assertEqual((out / 'code.bin').read_bytes(), code)
            self.assertEqual(record['calls'][0]['sdk_names'], ['DrawSync'])
            self.assertEqual(record['calls'][0]['return_address'], '0x80081010')
            self.assertIn('DrawSync', (out / 'draft.c').read_text())
            if llvm:
                self.assertTrue(record['disassembly_roundtrip_exact'])

    def test_rejects_invalid_ranges(self):
        for address, size in [(0x80010001, 4), (-4, 4), (0x100000000, 4),
                              (0x80010000, 0), (0x80010000, 3), (0x80010000, 260)]:
            with self.subTest(address=address, size=size), self.assertRaises(ValueError):
                PREPARE.validate_range(address, size)
        PREPARE.validate_range(0x80010000, 256)

    def test_call_metadata_preserves_links_and_unknown_targets(self):
        start = 0x8ffffffc
        target = 0x90001000
        jal = (3 << 26) | ((target >> 2) & 0x03ffffff)
        jalr_t9_ra = (25 << 21) | (31 << 11) | 9
        jalr_t9_zero = (25 << 21) | 9
        code = struct.pack('<5I', jal, 0, jalr_t9_ra, 0, jalr_t9_zero)
        calls = PREPARE.calls(code, start, {target: ['NamedSdk']})
        self.assertEqual(calls[0]['target'], '0x90001000')
        self.assertEqual(calls[0]['sdk_names'], ['NamedSdk'])
        self.assertEqual(calls[0]['return_address'], '0x90000004')
        self.assertIsNone(calls[1]['target'])
        self.assertEqual(calls[1]['link_register'], 31)
        self.assertIsNone(calls[2]['return_address'])
        self.assertFalse(calls[2]['delay_slot_in_range'])

    def test_external_bindings_do_not_replace_local_labels_or_instructions(self):
        asm = 'func_80010000:\njal NamedSdk\n.L80010008:\nlui $v0,%hi(D_80020000)\n'
        result = PREPARE.assembly_bindings(asm, {'NamedSdk': 0x80030000}, 0x80010000, 0x80010010)
        self.assertTrue(result.endswith(asm))
        self.assertIn('.equ NamedSdk, 0x80030000', result)
        self.assertIn('.equ D_80020000, 0x80020000', result)
        self.assertNotIn('.equ func_80010000', result)
        self.assertNotIn('.equ .L80010008', result)

    def test_named_sdk_body_is_not_sent_to_external_tools(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            exe = root / 'synthetic-exe'
            address = 0x80086530  # A name already present in our SDK table.
            data = bytearray(0x800)
            data[:8] = b'PS-X EXE'
            struct.pack_into('<II', data, 0x18, address, 8)
            exe.write_bytes(data + struct.pack('<II', 0x03e00008, 0))
            out = root / 'build/analysis/functions/80086530'
            out.mkdir(parents=True)
            (out / 'task.json').write_text('stale success')
            (out / 'draft.c').write_text('stale draft')
            args = argparse.Namespace(exe=exe, address=address, size=8, python=Path(sys.executable),
                                      context=None, llvm_mc=None)
            with patch.object(PREPARE, 'ROOT', root), patch.object(PREPARE.subprocess, 'run') as run:
                with self.assertRaisesRegex(ValueError, 'named SDK entry'):
                    PREPARE.run(args)
                run.assert_not_called()
            self.assertFalse((out / 'task.json').exists())
            self.assertFalse((out / 'draft.c').exists())


if __name__ == '__main__':
    unittest.main()
