# SPDX-License-Identifier: GPL-3.0-or-later

import importlib.util
import io
import struct
import sys
import tempfile
import unittest
from contextlib import redirect_stderr
from pathlib import Path


def load_slice():
    path = Path(__file__).resolve().parents[1] / "tools" / "boot_slice.py"
    spec = importlib.util.spec_from_file_location("am3d_boot_slice", path)
    module = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = module
    spec.loader.exec_module(module)
    return module


SLICE = load_slice()
LOAD = 0x80010000


def make_exe(text):
    blob = bytearray(0x800) + bytearray(text)
    blob[0:8] = b"PS-X EXE"
    struct.pack_into("<IIII", blob, 0x10, LOAD, 0, LOAD, len(text))
    return bytes(blob)


def words(*values):
    return struct.pack("<" + "I" * len(values), *values)


def jal(addr, target):
    return 0x0C000000 | ((target >> 2) & 0x03FFFFFF)


class BootSliceTests(unittest.TestCase):
    def test_unnamed_jal_keeps_delay_slot_args(self):
        blob = words(
            0x24040100,  # addiu a0, zero, 0x100
            jal(LOAD + 4, 0x80010040),
            0x24050078,  # addiu a1, zero, 0x78
            0x00000000,
        )
        report = SLICE.slice_text(blob, LOAD, LOAD, {}, [], Path("missing"))
        self.assertIn("0x80010004  jal 0x80010040\n", report)
        self.assertIn("0x80010008  addiu a1, zero, 0x78\n", report)
        self.assertIn("stop unnamed-jal\n", report)
        self.assertIn("args a0=0x00000100 a1=0x00000078\n", report)
        self.assertIn("ra 0x8001000c\n", report)
        self.assertTrue(report.endswith("next 0x80010040\n"))

    def test_unnamed_callee_returns_to_the_caller(self):
        blob = words(
            jal(LOAD, 0x80010018),
            0x00000000,
            0x24020007,  # addiu v0, zero, 7, after the call
            0x03E00008,
            0x00000000,
            0x00000000,
            0x03E00008,  # callee jr ra
            0x00000000,
        )
        report = SLICE.slice_text(blob, LOAD, LOAD, {}, [], Path("missing"))
        self.assertIn("0x80010018  jr ra\n", report)
        self.assertIn("return 0x80010008\n", report)
        self.assertIn("0x80010008  addiu v0, zero, 0x7\n", report)
        self.assertIn("stop jr\n", report)

    def test_named_call_continues_at_return(self):
        # jal named 0x80010020, delay nop, then jr ra, delay nop.
        blob = words(
            jal(LOAD, 0x80010020),
            0x00000000,
            0x03E00008,
            0x00000000,
            0x24020063,  # body must not appear
        )
        report = SLICE.slice_text(
            blob, LOAD, LOAD, {0x80010020: "ClearOTagR"}, [], Path("missing")
        )
        self.assertNotIn("0x80010010", report)
        self.assertIn("ClearOTagR sdk", report)
        self.assertIn("stop jr\n", report)
        self.assertIn("ra 0x80010008\n", report)
        self.assertTrue(report.endswith("next 0x80010008\n"))

    def test_existing_note_skips_the_body(self):
        blob = words(
            jal(LOAD, 0x80010020),
            0x24040100,
            0x03E00008,
            0x00000000,
        )
        with tempfile.TemporaryDirectory() as tmp:
            notes = Path(tmp)
            (notes / "call-80010020.md").write_text("traced\n", encoding="utf-8")
            report = SLICE.slice_text(blob, LOAD, LOAD, {}, [], notes)
        self.assertIn("noted note", report)
        self.assertIn("args a0=0x00000100\n", report)
        self.assertIn("stop jr\n", report)

    def test_branch_stops_without_a_taken_side(self):
        blob = words(
            0x10800002,  # beq a0, zero, +2 -> 0x80010010
            0x00000000,
            0x24020001,
            0x00000000,
        )
        report = SLICE.slice_text(blob, LOAD, LOAD, {}, [], Path("missing"))
        self.assertIn("stop branch\n", report)
        self.assertIn("branch 0x80010000 taken 0x8001000c fall 0x80010008\n", report)
        self.assertNotIn("0x80010008  addiu", report)
        self.assertTrue(report.endswith("next unknown\n"))

    def test_known_branch_follows_the_taken_side(self):
        blob = words(
            0x24040000,  # addiu a0, zero, 0
            0x10800003,  # beq a0, zero, +3 -> 0x80010014
            0x00000000,
            0x24020001,  # fall, not reached
            0x03E00008,
            0x24020002,  # taken
            0x03E00008,
            0x00000000,
        )
        report = SLICE.slice_text(blob, LOAD, LOAD, {}, [], Path("missing"))
        self.assertIn("branch 0x80010004 taken 0x80010014\n", report)
        self.assertIn("0x80010014  addiu v0, zero, 0x2\n", report)
        self.assertNotIn("0x8001000c", report)
        self.assertIn("stop jr\n", report)

    def test_known_branch_follows_the_fall_side(self):
        blob = words(
            0x24040001,  # addiu a0, zero, 1
            0x10800003,  # beq a0, zero, +3
            0x00000000,
            0x03E00008,  # fall
            0x00000000,
            0x24020009,  # taken, not reached
        )
        report = SLICE.slice_text(blob, LOAD, LOAD, {}, [], Path("missing"))
        self.assertIn("branch 0x80010004 fall 0x8001000c\n", report)
        self.assertIn("stop jr\n", report)
        self.assertNotIn("addiu v0, zero, 0x9", report)

    def test_stored_word_reaches_a_later_load(self):
        blob = words(
            0x3C108002,  # lui s0, 0x8002
            0x24080100,  # addiu t0, zero, 0x100
            0xAE080000,  # sw t0, 0(s0)
            0x8E040000,  # lw a0, 0(s0)
            jal(LOAD + 16, 0x80010040),
            0x00000000,
        )
        report = SLICE.slice_text(blob, LOAD, LOAD, {}, [], Path("missing"))
        self.assertIn("args a0=0x00000100 mem\n", report)

    def test_word_fill_drops_the_stored_word(self):
        blob = words(
            0x3C108002,  # lui s0, 0x8002
            0x24080111,  # addiu t0, zero, 0x11
            0xAE080000,  # sw t0, 0(s0)
            0x02002021,  # addu a0, s0, zero
            jal(LOAD + 16, 0x80010080),
            0x24060004,  # addiu a2, zero, 4
            0x8E040000,  # lw a0, 0(s0)
            jal(LOAD + 28, 0x80010040),
            0x00000000,
        )
        report = SLICE.slice_text(
            blob, LOAD, LOAD, {0x80010080: "word_fill"}, [], Path("missing")
        )
        self.assertIn("word_fill sdk", report)
        self.assertIn("args unknown\n", report)

    def test_jump_is_followed_until_it_loops(self):
        blob = words(
            0x08004002,  # j 0x80010008
            0x24040001,  # addiu a0, zero, 1
            0x08004000,  # j 0x80010000
            0x00000000,
        )
        report = SLICE.slice_text(blob, LOAD, LOAD, {}, [], Path("missing"))
        self.assertIn("0x80010008  j 0x80010000\n", report)
        self.assertIn("stop loop\n", report)
        self.assertTrue(report.endswith("next 0x80010000\n"))

    def test_lui_ori_argument(self):
        blob = words(
            0x3C048001,  # lui a0, 0x8001
            0x34840020,  # ori a0, a0, 0x20
            jal(LOAD + 8, 0x80010040),
            0x00000000,
        )
        report = SLICE.slice_text(blob, LOAD, LOAD, {}, [], Path("missing"))
        self.assertIn("args a0=0x80010020\n", report)

    def test_bios_call_is_named(self):
        blob = words(
            0x2409002B,  # addiu t1, zero, 0x2b
            0x240200A0,  # addiu v0, zero, 0xa0
            0x0040F809,  # jalr v0
            0x00000000,
            0x03E00008,
            0x00000000,
        )
        report = SLICE.slice_text(blob, LOAD, LOAD, {}, [], Path("missing"))
        self.assertIn("jalr 0x000000a0 BIOS-A bios t1=0x0000002b", report)
        self.assertIn("stop jr\n", report)

    def test_saved_ra_returns_through_jr(self):
        blob = words(
            0x27BDFFE8,  # addiu sp, sp, -0x18
            0xAFBF0010,  # sw ra, 0x10(sp)
            0x8FBF0010,  # lw ra, 0x10(sp)
            0x03E00008,  # jr ra
            0x27BD0018,  # addiu sp, sp, 0x18
        )
        report = SLICE.slice_text(
            blob, LOAD, LOAD, {}, [], Path("missing"), ra=0x800253F4
        )
        self.assertTrue(report.endswith("next 0x800253f4\n"))

    def test_max_stops_early(self):
        blob = words(*([0x24040001] * 8))
        report = SLICE.slice_text(
            blob, LOAD, LOAD, {}, [], Path("missing"), limit=4
        )
        self.assertIn("count 4\n", report)
        self.assertIn("stop cap\n", report)

    def test_cap_stops_at_64(self):
        blob = words(*([0x24040001] * 70))
        report = SLICE.slice_text(blob, LOAD, LOAD, {}, [], Path("missing"))
        self.assertIn("count 64\n", report)
        self.assertIn("stop cap\n", report)
        self.assertTrue(report.endswith("next 0x80010100\n"))

    def test_main_rejects_a_bad_file(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            exe = root / "SLUS"
            out = root / "boot-slice.txt"
            exe.write_bytes(b"not an exe")
            stderr = io.StringIO()
            with redirect_stderr(stderr):
                rc = SLICE.main([str(exe), "--start", "0x80010000"], out_path=out)
        self.assertEqual(rc, 1)
        self.assertIn("bad magic", stderr.getvalue())
        self.assertFalse(out.exists())

    def test_main_writes_the_local_report(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            exe = root / "SLUS"
            out = root / "boot-slice.txt"
            notes = root / "notes"
            notes.mkdir()
            exe.write_bytes(make_exe(words(0x03E00008, 0x00000000)))
            rc = SLICE.main(
                [str(exe), "--start", hex(LOAD), "--notes", str(notes)],
                out_path=out,
            )
            text = out.read_text(encoding="utf-8")
        self.assertEqual(rc, 0)
        self.assertIn("stop jr\n", text)


if __name__ == "__main__":
    unittest.main()
