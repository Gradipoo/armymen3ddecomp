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
