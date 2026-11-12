# SPDX-License-Identifier: GPL-3.0-or-later
"""List // gap: comments and functions our notes do not cite yet.

Scans C, C++, headers, and Markdown. When docs/research/re/game-functions.tsv
exists, also lists functions whose address is missing from docs/research and
components. The TSV itself does not count as a citation. Exits 0 either way.

    python tools/gaps.py
    python tools/gaps.py --limit 20
"""

from __future__ import annotations

import argparse
import os
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
MARKER = "// gap:"
SOURCE_SUFFIXES = {".c", ".h", ".cpp", ".hpp", ".cc", ".hh", ".cxx", ".hxx", ".md"}
SKIP_NAMES = {"army men 3d (usa)", ".git", "__pycache__", "build"}
TSV_REL = Path("docs") / "research" / "re" / "game-functions.tsv"
PROJECT = "tools/ghidra/project"


def _skip_dir(name: str, rel: str) -> bool:
    if name.casefold() in SKIP_NAMES:
        return True
    folded = rel.casefold()
    return folded == PROJECT or folded.startswith(PROJECT + "/")


def _gap_comments(root: Path) -> list[str]:
    found: list[str] = []
    for dirpath, dirnames, filenames in os.walk(root, followlinks=False):
        current = Path(dirpath)
        rel_dir = current.relative_to(root).as_posix()
        if rel_dir == ".":
            rel_dir = ""
        kept = []
        for name in dirnames:
            rel = f"{rel_dir}/{name}" if rel_dir else name
            if not _skip_dir(name, rel):
                kept.append(name)
        dirnames[:] = kept
        for name in filenames:
            path = current / name
            if path.suffix.lower() not in SOURCE_SUFFIXES or path.is_symlink():
                continue
            rel = path.relative_to(root).as_posix()
            try:
                text = path.read_text(encoding="utf-8", errors="replace")
            except OSError:
                continue
            for number, line in enumerate(text.splitlines(), 1):
                if MARKER in line:
                    found.append(f"{rel}:{number}: {line.strip()}")
    return found


def _norm_addr(text: str) -> str | None:
    raw = text.strip().lower()
    if raw.startswith("0x"):
        raw = raw[2:]
    try:
        return f"{int(raw, 16):08x}"
    except ValueError:
        return None


def _load_functions(tsv: Path) -> list[tuple[str, str]]:
    rows: list[tuple[str, str]] = []
    text = tsv.read_text(encoding="utf-8", errors="replace")
    for line in text.splitlines():
        if not line.strip():
            continue
        parts = line.split("\t")
        if len(parts) < 3 or parts[0].strip().lower() == "address":
            continue
        addr = _norm_addr(parts[0])
        if addr is None:
            continue
        rows.append((addr, parts[2].strip()))
    return rows


def _citation_text(root: Path, tsv: Path) -> str:
    chunks: list[str] = []
    try:
        tsv_resolved = tsv.resolve()
    except OSError:
        tsv_resolved = tsv
    for base in (root / "docs" / "research", root / "components"):
        if not base.is_dir():
            continue
        for dirpath, dirnames, filenames in os.walk(base, followlinks=False):
            dirnames[:] = [name for name in dirnames if name.casefold() not in {".git", "__pycache__"}]
            for name in filenames:
                path = Path(dirpath) / name
                if path.is_symlink():
                    continue
                try:
                    if path.resolve() == tsv_resolved:
                        continue
                    chunks.append(path.read_text(encoding="utf-8", errors="replace"))
                except OSError:
                    continue
    return "\n".join(chunks).lower()


def _uncited(root: Path) -> list[str] | None:
    tsv = root / TSV_REL
    if not tsv.is_file():
        return None
    haystack = _citation_text(root, tsv)
    missing: list[str] = []
    seen: set[str] = set()
    for addr, name in _load_functions(tsv):
        if addr in seen:
            continue
        seen.add(addr)
        if addr not in haystack:
            missing.append(f"{addr} {name}")
    return missing


def _print_section(title: str, items: list[str], limit: int | None) -> None:
    print(title)
    shown = items if limit is None else items[:limit]
    if not shown:
        print("(none)")
    else:
        for item in shown:
            print(item)
    extra = len(items) - len(shown)
    if extra:
        print(f"... {extra} more")


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description="List gap comments and functions that are not cited yet.")
    parser.add_argument("--limit", type=int, default=None, help="Max items to print in each list.")
    parser.add_argument("--root", type=Path, help="Tree to scan. Default: the repo root.")
    args = parser.parse_args(argv)
    if args.limit is not None and args.limit < 0:
        print("error: --limit must be >= 0", file=sys.stderr)
        return 2
    root = (args.root if args.root is not None else ROOT).resolve()
    if not root.is_dir():
        print(f"error: root not found: {root}", file=sys.stderr)
        return 1
    _print_section("// gap:", _gap_comments(root), args.limit)
    missing = _uncited(root)
    if missing is None:
        print("uncited:")
        print("(no game-functions.tsv)")
    else:
        _print_section("uncited:", missing, args.limit)
    return 0


if __name__ == "__main__":
    sys.exit(main())
