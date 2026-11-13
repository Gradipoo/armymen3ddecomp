# SPDX-License-Identifier: GPL-3.0-or-later

import importlib.util
import io
import struct
import sys
import tempfile
import unittest
from contextlib import redirect_stderr, redirect_stdout
from pathlib import Path


def load_sdk_scan():
    path = Path(__file__).resolve().parents[1] / "tools" / "sdk_scan.py"
    spec = importlib.util.spec_from_file_location("am3d_sdk_scan", path)
    module = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = module
    spec.loader.exec_module(module)
    return module


SCAN = load_sdk_scan()

MASKED_JSON = """[
  {
    "sig": "11 22 ?? 44 55 66 77 88 99 AA BB CC",
    "labels": [
      {"name": "MaskedFn", "offset": 0},
      {"name": "InnerFn", "offset": 4},
      {"name": "PastFn", "offset": 12}
    ]
  }
]
"""

PLANTED = bytes.fromhex("11 22 AB 44 55 66 77 88 99 AA BB CC")

SHORT_JSON = """[
  {
    "sig": "01 02 03 04 05 06 07 ?? ??",
    "labels": [
      {"name": "TooShort", "offset": 0}
    ]
  }
]
"""

SHORT_BYTES = bytes.fromhex("01 02 03 04 05 06 07 AB CD")


def make_exe(pc, gp, load_addr, text):
    blob = bytearray(0x800) + bytearray(text)
    blob[0:8] = b"PS-X EXE"
    struct.pack_into("<IIII", blob, 0x10, pc, gp, load_addr, len(text))
    return bytes(blob)


def write_sigs(root, body, version="460"):
    folder = root / version
    folder.mkdir()
    (folder / "lib.json").write_text(body, encoding="utf-8")
    return root


MIXED_JSON = """[
  {
    "name": "BSS.OBJ",
    "xbss": [{"name": "pad", "size": 4}]
  },
  {
    "sig": "11 22 ?? 44 55 66 77 88 99 AA BB CC",
    "labels": [
      {"name": "MaskedFn", "offset": 0}
    ]
  }
]
"""


class SdkScanTests(unittest.TestCase):
    def test_masked_pattern_hits(self):
        load = 0x80030000
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            exe = root / "SLUS"
            exe.write_bytes(make_exe(0x80012345, 0x8002ABCD, load, PLANTED))
            write_sigs(root, MASKED_JSON)
            stdout = io.StringIO()
            stderr = io.StringIO()
            with redirect_stdout(stdout), redirect_stderr(stderr):
                rc = SCAN.main([str(exe), str(root)])
        self.assertEqual(rc, 0)
        self.assertEqual(stderr.getvalue(), "")
        self.assertEqual(
            stdout.getvalue(),
            f"0x{load:08x} MaskedFn 460\n0x{load + 4:08x} InnerFn 460\n",
        )

    def test_object_without_sig_is_skipped(self):
        load = 0x80030000
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            exe = root / "SLUS"
            exe.write_bytes(make_exe(0x80012345, 0x8002ABCD, load, PLANTED))
            write_sigs(root, MIXED_JSON)
            stdout = io.StringIO()
            stderr = io.StringIO()
            with redirect_stdout(stdout), redirect_stderr(stderr):
                rc = SCAN.main([str(exe), str(root)])
        self.assertEqual(rc, 0)
        self.assertEqual(stderr.getvalue(), "")
        self.assertEqual(stdout.getvalue(), f"0x{load:08x} MaskedFn 460\n")

    def test_shifted_pattern_misses(self):
        load = 0x80030000
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            exe = root / "SLUS"
            exe.write_bytes(make_exe(0x80012345, 0x8002ABCD, load, b"\x00" + PLANTED))
            write_sigs(root, MASKED_JSON)
            stdout = io.StringIO()
            stderr = io.StringIO()
            with redirect_stdout(stdout), redirect_stderr(stderr):
                rc = SCAN.main([str(exe), str(root)])
        self.assertEqual(rc, 0)
        self.assertEqual(stderr.getvalue(), "")
        self.assertEqual(stdout.getvalue(), "")

    def test_short_pattern_misses(self):
        load = 0x80030000
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            exe = root / "SLUS"
            exe.write_bytes(make_exe(0x80012345, 0x8002ABCD, load, SHORT_BYTES))
            write_sigs(root, SHORT_JSON)
            stdout = io.StringIO()
            stderr = io.StringIO()
            with redirect_stdout(stdout), redirect_stderr(stderr):
                rc = SCAN.main([str(exe), str(root)])
        self.assertEqual(rc, 0)
        self.assertEqual(stderr.getvalue(), "")
        self.assertEqual(stdout.getvalue(), "")

    def test_bad_magic_exits_nonzero(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            exe = root / "SLUS"
            exe.write_bytes(b"NOT AN EX" + b"\x00" * 32)
            write_sigs(root, MASKED_JSON)
            stdout = io.StringIO()
            stderr = io.StringIO()
            with redirect_stdout(stdout), redirect_stderr(stderr):
                rc = SCAN.main([str(exe), str(root)])
        self.assertNotEqual(rc, 0)
        self.assertEqual(stdout.getvalue(), "")
        self.assertIn("magic", stderr.getvalue())

    def test_truncated_header_exits_nonzero(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            exe = root / "SLUS"
            exe.write_bytes(b"PS-X EXE" + b"\x00" * 4)
            write_sigs(root, "[]")
            stderr = io.StringIO()
            with redirect_stderr(stderr):
                rc = SCAN.main([str(exe), str(root)])
        self.assertNotEqual(rc, 0)
        self.assertIn("truncated", stderr.getvalue())

    def test_missing_file_exits_nonzero(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            missing = root / "missing"
            write_sigs(root, "[]")
            stdout = io.StringIO()
            stderr = io.StringIO()
            with redirect_stdout(stdout), redirect_stderr(stderr):
                rc = SCAN.main([str(missing), str(root)])
        self.assertNotEqual(rc, 0)
        self.assertEqual(stdout.getvalue(), "")
        self.assertIn("not found", stderr.getvalue())

    def test_bad_directory_exits_nonzero(self):
        load = 0x80030000
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            exe = root / "SLUS"
            exe.write_bytes(make_exe(0x80012345, 0x8002ABCD, load, PLANTED))
            missing = root / "no_sigs"
            stdout = io.StringIO()
            stderr = io.StringIO()
            with redirect_stdout(stdout), redirect_stderr(stderr):
                rc = SCAN.main([str(exe), str(missing)])
        self.assertNotEqual(rc, 0)
        self.assertEqual(stdout.getvalue(), "")
        self.assertIn("directory", stderr.getvalue())

    def test_unreadable_json_exits_nonzero(self):
        load = 0x80030000
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            exe = root / "SLUS"
            exe.write_bytes(make_exe(0x80012345, 0x8002ABCD, load, PLANTED))
            write_sigs(root, "{")
            stdout = io.StringIO()
            stderr = io.StringIO()
            with redirect_stdout(stdout), redirect_stderr(stderr):
                rc = SCAN.main([str(exe), str(root)])
        self.assertNotEqual(rc, 0)
        self.assertEqual(stdout.getvalue(), "")
        self.assertIn("unreadable", stderr.getvalue())


if __name__ == "__main__":
    unittest.main()
