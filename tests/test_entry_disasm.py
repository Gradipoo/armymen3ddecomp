# SPDX-License-Identifier: GPL-3.0-or-later

import importlib.util
import io
import struct
import sys
import tempfile
import unittest
from contextlib import redirect_stderr
from pathlib import Path


def load_disasm():
    path = Path(__file__).resolve().parents[1] / "tools" / "entry_disasm.py"
    spec = importlib.util.spec_from_file_location("am3d_entry_disasm", path)
    module = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = module
    spec.loader.exec_module(module)
    return module


DISASM = load_disasm()
LOAD = 0x80010000


def make_exe(pc, text):
    blob = bytearray(0x800) + bytearray(text)
    blob[0:8] = b"PS-X EXE"
    struct.pack_into("<IIII", blob, 0x10, pc, 0, LOAD, len(text))
    return bytes(blob)


def synthetic_text():
    # Entry block, then a later block. The default path must stay on the entry.
    words = (
        0x24080001,  # 0x80010000 addiu t0, zero, 1
        0x24090002,  # 0x80010004 addiu t1, zero, 2
        0x0C004008,  # 0x80010008 jal 0x80010020
        0x00000000,  # 0x8001000c nop, delay slot, not included
        0x24020007,  # 0x80010010 addiu v0, zero, 7
        0x03E00008,  # 0x80010014 jr ra
        0x24040009,  # 0x80010018 addiu a0, zero, 9, not included
    )
    return struct.pack("<" + "I" * len(words), *words)


class EntryDisasmTests(unittest.TestCase):
    def test_default_follows_header_pc(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            exe = root / "SLUS"
            out = root / "entry-disasm.txt"
            exe.write_bytes(make_exe(LOAD, synthetic_text()))
            stderr = io.StringIO()
            with redirect_stderr(stderr):
                rc = DISASM.main([str(exe)], out_path=out)
            text = out.read_text(encoding="utf-8")
            err = stderr.getvalue()
        self.assertEqual(rc, 0)
        self.assertEqual(err, "")
        self.assertEqual(
            text,
            "0x80010000  addiu t0, zero, 0x1\n"
            "0x80010004  addiu t1, zero, 0x2\n"
            "0x80010008  jal 0x80010020\n",
        )

    def test_start_address_overrides_entry(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            exe = root / "SLUS"
            out = root / "entry-disasm.txt"
            exe.write_bytes(make_exe(LOAD, synthetic_text()))
            rc = DISASM.main(
                [str(exe), "--start", "0x80010010"],
                out_path=out,
            )
            text = out.read_text(encoding="utf-8")
        self.assertEqual(rc, 0)
        self.assertEqual(
            text,
            "0x80010010  addiu v0, zero, 0x7\n"
            "0x80010014  jr ra\n",
        )


if __name__ == "__main__":
    unittest.main()
