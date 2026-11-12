# SPDX-License-Identifier: GPL-3.0-or-later
"""Fail if the tree contains game data or decompiler output.

Skips the retail disc directory (never opened) and paths ignored by a
simple reading of .gitignore. Exits 1 when a file that is not ignored is
a .bin, .cue, or .iso, starts with "PS-X EXE", is *.decomp.c or *.c.ghidra,
or lives under tools/ghidra/project. Also exits 1 when .gitignore does not
contain "Army Men 3D (USA)/".

    python tools/pr_guard.py
    python tools/pr_guard.py --root path/to/tree
"""

from __future__ import annotations

import argparse
import fnmatch
import os
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
REQUIRED = "Army Men 3D (USA)/"
PROJECT = "tools/ghidra/project"
# The retail disc folder is never part of the tree we check, and we do not open it.
NEVER_ENTER = {"army men 3d (usa)", ".git", "__pycache__"}
# Until .gitignore exists, still ignore the disc dumps and build outputs.
FALLBACK = [
    "Army Men 3D (USA)/",
    "*.bin",
    "*.cue",
    "*.iso",
    "build/",
]
BAD_SUFFIXES = (".bin", ".cue", ".iso", ".decomp.c", ".c.ghidra")
MAGIC = b"PS-X EXE"


def _read_gitignore(root: Path) -> str | None:
    path = root / ".gitignore"
    if not path.is_file() or path.is_symlink():
        return None
    data = path.read_bytes()
    try:
        return data.decode("utf-8")
    except UnicodeDecodeError:
        return data.decode("latin-1")


def _parse_gitignore(text: str) -> list[str]:
    patterns: list[str] = []
    for raw in text.splitlines():
        line = raw.strip()
        # The published ignore list has no '!' exceptions.
        if not line or line.startswith("#") or line.startswith("!"):
            continue
        patterns.append(line)
    return patterns


def _path_match(pattern: str, rel: str) -> bool:
    pat_parts = pattern.split("/")
    rel_parts = rel.split("/")
    if len(pat_parts) != len(rel_parts):
        return False
    for pat, part in zip(pat_parts, rel_parts):
        if not fnmatch.fnmatchcase(part.casefold(), pat.casefold()):
            return False
    return True


def _match_pattern(pattern: str, rel: str, is_dir: bool) -> bool:
    dir_only = pattern.endswith("/")
    anchored = pattern.startswith("/") or "/" in pattern.strip("/")
    body = pattern[1:] if pattern.startswith("/") else pattern
    body = body.strip("/")
    if not body:
        return False
    if anchored:
        if dir_only and not is_dir:
            return False
        return _path_match(body, rel)
    if dir_only and not is_dir:
        return False
    base = rel.rsplit("/", 1)[-1]
    return fnmatch.fnmatchcase(base.casefold(), body.casefold())


def _ignored(rel: str, is_dir: bool, patterns: list[str]) -> bool:
    return any(_match_pattern(pattern, rel, is_dir) for pattern in patterns)


def _is_project(rel: str) -> bool:
    folded = rel.casefold()
    return folded == PROJECT or folded.startswith(PROJECT + "/")


def check(root: Path) -> list[str]:
    root = root.resolve()
    problems: list[str] = []
    text = _read_gitignore(root)
    if text is None or REQUIRED not in text:
        problems.append("gitignore does not contain 'Army Men 3D (USA)/'")
    patterns = _parse_gitignore(text) if text is not None else list(FALLBACK)

    for dirpath, dirnames, filenames in os.walk(root, followlinks=False):
        current = Path(dirpath)
        rel_dir = current.relative_to(root).as_posix()
        if rel_dir == ".":
            rel_dir = ""
        kept: list[str] = []
        for name in dirnames:
            rel = f"{rel_dir}/{name}" if rel_dir else name
            if name.casefold() in NEVER_ENTER:
                continue
            if _is_project(rel):
                if not _ignored(rel, True, patterns):
                    problems.append(rel)
                continue
            if _ignored(rel, True, patterns):
                continue
            kept.append(name)
        dirnames[:] = kept
        for name in filenames:
            rel = f"{rel_dir}/{name}" if rel_dir else name
            if _ignored(rel, False, patterns):
                continue
            if _is_project(rel):
                problems.append(rel)
                continue
            if name.lower().endswith(BAD_SUFFIXES):
                problems.append(rel)
                continue
            path = current / name
            if path.is_symlink():
                continue
            try:
                with path.open("rb") as handle:
                    magic = handle.read(8)
            except OSError as exc:
                problems.append(f"{rel}: {exc}")
                continue
            if magic == MAGIC:
                problems.append(rel)
    return sorted(set(problems))


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description="Fail if game data or decompiler output is in the tree.")
    parser.add_argument("--root", type=Path, help="Tree to check. Default: the repo root.")
    args = parser.parse_args(argv)
    root = args.root if args.root is not None else ROOT
    if not root.is_dir():
        print(f"error: root not found: {root}", file=sys.stderr)
        return 1
    problems = check(root)
    for item in problems:
        print(item, file=sys.stderr)
    return 1 if problems else 0


if __name__ == "__main__":
    sys.exit(main())
