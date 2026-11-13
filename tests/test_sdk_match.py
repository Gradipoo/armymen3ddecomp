# SPDX-License-Identifier: GPL-3.0-or-later

import importlib.util
import io
import struct
import sys
import tempfile
import unittest
from contextlib import redirect_stderr, redirect_stdout
from pathlib import Path


def load_sdk_match():
    path = Path(__file__).resolve().parents[1] / "tools" / "sdk_match.py"
    spec = importlib.util.spec_from_file_location("am3d_sdk_match", path)
    module = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = module
    spec.loader.exec_module(module)
    return module


MATCH = load_sdk_match()


def make_exe(pc, gp, load_addr, text):
    blob = bytearray(0x800) + bytearray(text)
    blob[0:8] = b"PS-X EXE"
    struct.pack_into("<IIII", blob, 0x10, pc, gp, load_addr, len(text))
    return bytes(blob)


class SdkMatchTests(unittest.TestCase):
    def pattern(self, name):
        patterns = dict(MATCH.load_patterns(MATCH.PATTERN_TABLE))
        return patterns[name]

    def test_planted_pattern_hits(self):
        pat = self.pattern("word_fill")
        load = 0x80030000
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "SLUS"
            path.write_bytes(make_exe(0x80012345, 0x8002ABCD, load, pat))
            stdout = io.StringIO()
            stderr = io.StringIO()
            with redirect_stdout(stdout), redirect_stderr(stderr):
                rc = MATCH.main([str(path)])
        self.assertEqual(rc, 0)
        self.assertEqual(stderr.getvalue(), "")
        self.assertEqual(stdout.getvalue(), f"0x{load:08x} word_fill\n")

    def test_shifted_pattern_misses(self):
        pat = self.pattern("word_fill")
        load = 0x80030000
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "SLUS"
            path.write_bytes(make_exe(0x80012345, 0x8002ABCD, load, b"\x00" + pat))
            stdout = io.StringIO()
            stderr = io.StringIO()
            with redirect_stdout(stdout), redirect_stderr(stderr):
                rc = MATCH.main([str(path)])
        self.assertEqual(rc, 0)
        self.assertEqual(stderr.getvalue(), "")
        self.assertEqual(stdout.getvalue(), "")

    def test_bad_magic_exits_nonzero(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "SLUS"
            path.write_bytes(b"NOT AN EX" + b"\x00" * 32)
            stdout = io.StringIO()
            stderr = io.StringIO()
            with redirect_stdout(stdout), redirect_stderr(stderr):
                rc = MATCH.main([str(path)])
        self.assertNotEqual(rc, 0)
        self.assertEqual(stdout.getvalue(), "")
        self.assertIn("magic", stderr.getvalue())

    def test_truncated_header_exits_nonzero(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "SLUS"
            path.write_bytes(b"PS-X EXE" + b"\x00" * 4)
            stderr = io.StringIO()
            with redirect_stderr(stderr):
                rc = MATCH.main([str(path)])
        self.assertNotEqual(rc, 0)
        self.assertIn("truncated", stderr.getvalue())

    def test_name_inside_text_is_printed(self):
        load = 0x80030000
        text = b"\x00" * 16
        with tempfile.TemporaryDirectory() as tmp:
            exe = Path(tmp) / "SLUS"
            exe.write_bytes(make_exe(0x80012345, 0x8002ABCD, load, text))
            names = Path(tmp) / "names.txt"
            names.write_text(f"0x{load:08x} CdInit\n0x80010000 absent\n")
            old = MATCH.NAME_TABLE
            MATCH.NAME_TABLE = names
            try:
                stdout = io.StringIO()
                stderr = io.StringIO()
                with redirect_stdout(stdout), redirect_stderr(stderr):
                    rc = MATCH.main([str(exe)])
            finally:
                MATCH.NAME_TABLE = old
        self.assertEqual(rc, 0)
        self.assertEqual(stderr.getvalue(), "")
        self.assertEqual(stdout.getvalue(), f"0x{load:08x} CdInit\n")

    def test_scan_keeps_aligned_hits_in_table_order(self):
        same = [
            ("first", b"\x11\x22\x33\x44"),
            ("second", b"\x11\x22\x33\x44"),
        ]
        hits = MATCH.scan(0x80000000, b"\x11\x22\x33\x44", same)
        self.assertEqual(
            hits,
            [
                (0x80000000, "first"),
                (0x80000000, "second"),
            ],
        )
        # The 11 22 33 44 copy is unaligned. The aa run hits at index 8 only.
        text = b"\x00" + b"\x11\x22\x33\x44" + (b"\xaa" * 8)
        hits = MATCH.scan(0x80000000, text, same + [("wide", b"\xaa\xaa\xaa\xaa")])
        self.assertEqual(hits, [(0x80000008, "wide")])
        hits = MATCH.scan(0x80000000, b"\xaa" * 8, [("wide", b"\xaa\xaa\xaa\xaa")])
        self.assertEqual(
            hits,
            [
                (0x80000000, "wide"),
                (0x80000004, "wide"),
            ],
        )

    def test_missing_file_exits_nonzero(self):
        with tempfile.TemporaryDirectory() as tmp:
            missing = Path(tmp) / "missing"
            stderr = io.StringIO()
            with redirect_stderr(stderr):
                rc = MATCH.main([str(missing)])
        self.assertNotEqual(rc, 0)
        self.assertIn("not found", stderr.getvalue())


if __name__ == "__main__":
    unittest.main()
