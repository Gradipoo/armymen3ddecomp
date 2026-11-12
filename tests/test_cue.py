# SPDX-License-Identifier: GPL-3.0-or-later

import importlib.util
import io
import os
import struct
import sys
import tempfile
import unittest
from contextlib import redirect_stderr, redirect_stdout
from pathlib import Path


def load_disc():
    path = Path(__file__).resolve().parents[1] / "tools" / "disc.py"
    spec = importlib.util.spec_from_file_location("am3d_disc", path)
    module = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = module
    spec.loader.exec_module(module)
    return module


DISC = load_disc()


def both16(value):
    return struct.pack("<H", value) + struct.pack(">H", value)


def both32(value):
    return struct.pack("<I", value) + struct.pack(">I", value)


def dir_record(extent, data_len, name, is_dir):
    size = 33 + len(name)
    if size % 2:
        size += 1
    rec = bytearray(size)
    rec[0] = size
    rec[2:10] = both32(extent)
    rec[10:18] = both32(data_len)
    rec[25] = 2 if is_dir else 0
    rec[28:32] = both16(1)
    rec[32] = len(name)
    rec[33:33 + len(name)] = name
    return bytes(rec)


def build_user_sectors(extra_records=()):
    payload = b"hello\n"
    root = dir_record(18, 2048, b"\x00", True)
    directory = b"".join(
        (
            dir_record(18, 2048, b"\x00", True),
            dir_record(18, 2048, b"\x01", True),
            dir_record(19, len(payload), b"HELLO.TXT;1", False),
            *extra_records,
        )
    )
    directory = directory + bytes(2048 - len(directory))
    label = b"AM3DTEST"
    pvd = bytearray(2048)
    pvd[0] = 1
    pvd[1:6] = b"CD001"
    pvd[6] = 1
    pvd[8:40] = b" " * 32
    pvd[40:72] = label + b" " * (32 - len(label))
    pvd[80:88] = both32(20)
    pvd[120:124] = both16(1)
    pvd[124:128] = both16(1)
    pvd[128:132] = both16(2048)
    pvd[156:156 + len(root)] = root
    pvd[881] = 1
    term = bytearray(2048)
    term[0] = 255
    term[1:6] = b"CD001"
    term[6] = 1
    file_sector = payload + bytes(2048 - len(payload))
    sectors = [bytes(2048) for _ in range(16)]
    sectors.append(bytes(pvd))
    sectors.append(bytes(term))
    sectors.append(directory)
    sectors.append(file_sector)
    if len(sectors) != 20 or any(len(item) != 2048 for item in sectors):
        raise AssertionError("synthetic image is the wrong shape")
    return sectors


def mode2_sector(user):
    sector = bytearray(2352)
    sector[1:11] = b"\xff" * 10
    sector[15] = 2
    sector[24:24 + 2048] = user
    return bytes(sector)


def write_tiny_disc(root, extra_records=()):
    bin_path = root / "track 01.bin"
    with bin_path.open("wb") as handle:
        for user in build_user_sectors(extra_records=extra_records):
            handle.write(mode2_sector(user))
    cue = root / "game.cue"
    cue.write_text(
        'FILE "track 01.bin" BINARY\n  TRACK 01 MODE2/2352\n    INDEX 01 00:00:00\n',
        encoding="utf-8",
    )
    return cue


class CueTests(unittest.TestCase):
    def test_mode2_user_data_is_2048_at_offset_24(self):
        payload = bytes(i & 0xFF for i in range(2048))
        sector = bytearray(2352)
        sector[0] = 0x00
        sector[1:11] = b"\xff" * 10
        sector[11] = 0x00
        sector[15] = 0x02
        sector[23] = 0x11
        sector[24:2072] = payload
        sector[2072] = 0x22
        self.assertEqual(DISC.mode2_user_data(bytes(sector)), payload)

    def test_short_sector_fails(self):
        with self.assertRaises(DISC.DiscError):
            DISC.mode2_user_data(b"x" * 16)

    def test_parse_msf(self):
        self.assertEqual(DISC.parse_msf("00:00:00"), 0)
        self.assertEqual(DISC.parse_msf("00:02:00"), 150)
        self.assertEqual(DISC.parse_msf("01:00:00"), 4500)

    def test_parse_cue_quoted_track(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            cue = root / "game.cue"
            cue.write_text(
                'FILE "track 01.bin" BINARY\n'
                "  TRACK 01 MODE2/2352\n"
                "    INDEX 01 00:00:00\n"
                'FILE "track 02.bin" BINARY\n'
                "  TRACK 02 AUDIO\n"
                "    INDEX 01 00:00:00\n",
                encoding="utf-8",
            )
            tracks = DISC.parse_cue(cue)
        self.assertEqual(tracks[0].number, 1)
        self.assertEqual(tracks[0].mode, "MODE2/2352")
        self.assertEqual(tracks[0].path, root / "track 01.bin")
        self.assertEqual(tracks[0].indexes[1], 0)
        self.assertEqual(tracks[1].mode, "AUDIO")

    def test_extract_tiny_iso(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            cue = write_tiny_disc(root)
            out = root / "out"
            stdout = io.StringIO()
            stderr = io.StringIO()
            with redirect_stdout(stdout), redirect_stderr(stderr):
                rc = DISC.main([str(cue), "--out", str(out)])
            self.assertEqual(rc, 0, stderr.getvalue())
            self.assertEqual((out / "HELLO.TXT").read_bytes(), b"hello\n")
            self.assertEqual(stdout.getvalue().strip(), "HELLO.TXT")

    def test_extract_skips_extent_outside_data_track(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            cue = write_tiny_disc(
                root,
                extra_records=(dir_record(126633, 2048, b"TRACK02.DA;1", False),),
            )
            out = root / "out"
            stdout = io.StringIO()
            stderr = io.StringIO()
            with redirect_stdout(stdout), redirect_stderr(stderr):
                rc = DISC.main([str(cue), "--out", str(out)])
            self.assertEqual(rc, 0, stderr.getvalue())
            self.assertEqual((out / "HELLO.TXT").read_bytes(), b"hello\n")
            self.assertEqual(stdout.getvalue().strip(), "HELLO.TXT")
            self.assertFalse((out / "TRACK02.DA").exists())

    def test_missing_cue_fails(self):
        with tempfile.TemporaryDirectory() as tmp:
            missing = Path(tmp) / "no-such.cue"
            out = Path(tmp) / "out"
            stderr = io.StringIO()
            with redirect_stderr(stderr):
                rc = DISC.main([str(missing), "--out", str(out)])
            self.assertNotEqual(rc, 0)
            self.assertIn("not found", stderr.getvalue().lower())
            self.assertFalse(out.exists())

    def test_missing_bin_fails(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            cue = root / "game.cue"
            cue.write_text(
                'FILE "missing.bin" BINARY\n  TRACK 01 MODE2/2352\n    INDEX 01 00:00:00\n',
                encoding="utf-8",
            )
            stderr = io.StringIO()
            with redirect_stderr(stderr):
                rc = DISC.main([str(cue), "--out", str(root / "out")])
        self.assertNotEqual(rc, 0)
        self.assertIn("not found", stderr.getvalue().lower())

    def test_no_cue_argument_fails_without_env(self):
        previous = os.environ.pop("AM3D_DISC", None)
        try:
            stderr = io.StringIO()
            with redirect_stderr(stderr):
                rc = DISC.main([])
            self.assertNotEqual(rc, 0)
            self.assertIn("AM3D_DISC", stderr.getvalue())
        finally:
            if previous is not None:
                os.environ["AM3D_DISC"] = previous


if __name__ == "__main__":
    unittest.main()
