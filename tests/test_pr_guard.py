# SPDX-License-Identifier: GPL-3.0-or-later

import importlib.util
import io
import sys
import tempfile
import unittest
from contextlib import redirect_stderr
from pathlib import Path


def load_guard():
    path = Path(__file__).resolve().parents[1] / "tools" / "pr_guard.py"
    spec = importlib.util.spec_from_file_location("am3d_pr_guard", path)
    module = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = module
    spec.loader.exec_module(module)
    return module


GUARD = load_guard()
KEEP = "Army Men 3D (USA)/\n"


def run(root):
    err = io.StringIO()
    with redirect_stderr(err):
        rc = GUARD.main(["--root", str(root)])
    return rc, err.getvalue()


class PrGuardTests(unittest.TestCase):
    def test_stray_bin_fails(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root / ".gitignore").write_text(KEEP, encoding="utf-8")
            (root / "game.bin").write_bytes(b"not a disc")
            rc, message = run(root)
        self.assertEqual(rc, 1)
        self.assertIn("game.bin", message)

    def test_gitignored_disc_folder_passes(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root / ".gitignore").write_text(KEEP + "disc/\n", encoding="utf-8")
            disc = root / "disc"
            disc.mkdir()
            (disc / "game.bin").write_bytes(b"not a disc")
            (root / "readme.md").write_text("ok\n", encoding="utf-8")
            rc, message = run(root)
        self.assertEqual(rc, 0, message)
        self.assertEqual(message, "")

    def test_missing_gitignore_line_fails(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root / ".gitignore").write_text("*.bin\n", encoding="utf-8")
            rc, message = run(root)
        self.assertEqual(rc, 1)
        self.assertIn("Army Men 3D (USA)/", message)

    def test_psx_exe_magic_fails(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root / ".gitignore").write_text(KEEP, encoding="utf-8")
            (root / "SLUS_004.91").write_bytes(b"PS-X EXE" + b"\x00" * 32)
            rc, message = run(root)
        self.assertEqual(rc, 1)
        self.assertIn("SLUS_004.91", message)

    def test_retail_folder_is_skipped_without_gitignore(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            disc = root / "Army Men 3D (USA)"
            disc.mkdir()
            (disc / "SLUS_004.91").write_bytes(b"PS-X EXE" + b"\x00" * 16)
            rc, message = run(root)
        self.assertEqual(rc, 1)
        self.assertNotIn("SLUS_004.91", message)
        self.assertIn("Army Men 3D (USA)/", message)

    def test_decompiler_output_fails(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root / ".gitignore").write_text(KEEP, encoding="utf-8")
            (root / "func.decomp.c").write_text("int x;\n", encoding="utf-8")
            (root / "func.c.ghidra").write_text("int y;\n", encoding="utf-8")
            rc, message = run(root)
        self.assertEqual(rc, 1)
        self.assertIn("func.decomp.c", message)
        self.assertIn("func.c.ghidra", message)

    def test_ghidra_project_fails_when_not_ignored(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root / ".gitignore").write_text(KEEP, encoding="utf-8")
            project = root / "tools" / "ghidra" / "project"
            project.mkdir(parents=True)
            (project / "am3d.gpr").write_text("x", encoding="utf-8")
            rc, message = run(root)
        self.assertEqual(rc, 1)
        self.assertIn("tools/ghidra/project", message)


if __name__ == "__main__":
    unittest.main()
