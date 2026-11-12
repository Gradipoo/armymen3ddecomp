# SPDX-License-Identifier: GPL-3.0-or-later

import importlib.util
import io
import sys
import tempfile
import unittest
from contextlib import redirect_stdout
from pathlib import Path


def load_gaps():
    path = Path(__file__).resolve().parents[1] / "tools" / "gaps.py"
    spec = importlib.util.spec_from_file_location("am3d_gaps", path)
    module = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = module
    spec.loader.exec_module(module)
    return module


GAPS = load_gaps()


def write_tree(root):
    (root / "components").mkdir()
    (root / "components" / "load.cpp").write_text("// gap: entry\nsee 80010000\n", encoding="utf-8")
    (root / "docs" / "research").mkdir(parents=True)
    (root / "docs" / "research" / "note.md").write_text("// gap: note\n", encoding="utf-8")
    (root / "skip.py").write_text("// gap: not a source scan\n", encoding="utf-8")
    retail = root / "Army Men 3D (USA)"
    retail.mkdir()
    (retail / "hidden.cpp").write_text("// gap: should not appear\n", encoding="utf-8")
    tsv_dir = root / "docs" / "research" / "re"
    tsv_dir.mkdir()
    (tsv_dir / "game-functions.tsv").write_text(
        "address\tsize\tname\n80010000\t16\tcited\n80020000\t32\tmissing\n",
        encoding="utf-8",
    )


def run(root, limit=None):
    args = ["--root", str(root)]
    if limit is not None:
        args.extend(["--limit", str(limit)])
    stdout = io.StringIO()
    with redirect_stdout(stdout):
        rc = GAPS.main(args)
    return rc, stdout.getvalue()


class GapTests(unittest.TestCase):
    def test_lists_gaps_and_uncited_functions(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            write_tree(root)
            rc, text = run(root)
        self.assertEqual(rc, 0)
        self.assertIn("components/load.cpp:1: // gap: entry", text)
        self.assertIn("docs/research/note.md:1: // gap: note", text)
        self.assertNotIn("should not appear", text)
        self.assertNotIn("not a source scan", text)
        uncited = text.split("uncited:", 1)[1]
        self.assertIn("80020000 missing", uncited)
        self.assertNotIn("80010000", uncited)

    def test_limit_and_missing_tsv(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            write_tree(root)
            rc, text = run(root, limit=1)
            self.assertEqual(rc, 0)
            self.assertIn("... 1 more", text)
            self.assertNotIn("should not appear", text)
            (root / "docs" / "research" / "re" / "game-functions.tsv").unlink()
            rc, text = run(root)
        self.assertEqual(rc, 0)
        self.assertIn("(no game-functions.tsv)", text)


if __name__ == "__main__":
    unittest.main()
