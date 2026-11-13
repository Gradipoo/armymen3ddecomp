# SPDX-License-Identifier: GPL-3.0-or-later
"""Scan a PS-X EXE for masked signatures.

Magic is the 8 bytes "PS-X EXE". Load address and text size are
little-endian words at 0x18 and 0x1C. The text starts at file offset
0x800. file_off = 0x800 + (vaddr - load). The second argument is a
directory of signature JSON. Files in subdirectories are included.
Each file is an array of objects. A signature object has "sig" and
"labels". An object without those keys is skipped. A sig is
space-separated hex bytes. "??" is a wildcard. A label has "name" and
"offset". The version is the parent directory name. The scan steps 4
bytes. A hit needs at least 8 fixed bytes. A label whose offset lands
inside the hit prints one line: address, name, version.

    python tools/sdk_scan.py path/to/SLUS path/to/sigs
"""

from __future__ import annotations

import argparse
import json
import sys
from pathlib import Path

MAGIC = b"PS-X EXE"
TEXT_OFF = 0x800
STEP = 4
MIN_FIXED = 8

Pattern = tuple[int | None, ...]
Label = tuple[str, int]
Sig = tuple[Pattern, tuple[Label, ...], str]


class ToolError(Exception):
    pass


def read_exe(path: Path) -> tuple[int, bytes]:
    if not path.is_file():
        raise ToolError(f"file not found: {path}")
    with path.open("rb") as handle:
        data = handle.read()
    if len(data) < 8 or data[:8] != MAGIC:
        raise ToolError("not a PS-X EXE (bad magic)")
    if len(data) < 0x20:
        raise ToolError("PS-X EXE header is truncated")
    load = int.from_bytes(data[0x18:0x1C], "little")
    size = int.from_bytes(data[0x1C:0x20], "little")
    end = TEXT_OFF + size
    if len(data) < end:
        raise ToolError("PS-X EXE text is truncated")
    return load, data[TEXT_OFF:end]


def _parse_sig(text: object, path: Path) -> tuple[Pattern, int]:
    if not isinstance(text, str):
        raise ToolError(f"unreadable json: {path}")
    pattern: list[int | None] = []
    fixed = 0
    for part in text.split():
        if part == "??":
            pattern.append(None)
            continue
        if len(part) != 2 or not all(c in "0123456789abcdefABCDEF" for c in part):
            raise ToolError(f"unreadable json: {path}")
        pattern.append(int(part, 16))
        fixed += 1
    return tuple(pattern), fixed


def _parse_labels(raw: object, path: Path) -> tuple[Label, ...]:
    if not isinstance(raw, list):
        raise ToolError(f"unreadable json: {path}")
    labels: list[Label] = []
    for item in raw:
        if not isinstance(item, dict):
            raise ToolError(f"unreadable json: {path}")
        name = item.get("name")
        offset = item.get("offset")
        if not isinstance(name, str) or type(offset) is not int:
            raise ToolError(f"unreadable json: {path}")
        labels.append((name, offset))
    return tuple(labels)


def _parse_file(path: Path) -> list[Sig]:
    version = path.parent.name
    try:
        text = path.read_text(encoding="utf-8")
    except (OSError, UnicodeDecodeError):
        raise ToolError(f"unreadable json: {path}") from None
    try:
        data = json.loads(text)
    except json.JSONDecodeError:
        raise ToolError(f"unreadable json: {path}") from None
    if not isinstance(data, list):
        raise ToolError(f"unreadable json: {path}")
    sigs: list[Sig] = []
    for item in data:
        if not isinstance(item, dict):
            raise ToolError(f"unreadable json: {path}")
        if "sig" not in item or "labels" not in item:
            continue
        pattern, fixed = _parse_sig(item["sig"], path)
        labels = _parse_labels(item["labels"], path)
        if fixed < MIN_FIXED:
            continue
        sigs.append((pattern, labels, version))
    return sigs


def load_signatures(directory: Path) -> list[Sig]:
    if not directory.is_dir():
        raise ToolError(f"bad directory: {directory}")
    try:
        paths = sorted(directory.rglob("*.json"))
    except OSError:
        raise ToolError(f"bad directory: {directory}") from None
    sigs: list[Sig] = []
    for path in paths:
        if path.is_file():
            sigs.extend(_parse_file(path))
    return sigs


def _match(text: bytes, index: int, pattern: Pattern) -> bool:
    for offset, expected in enumerate(pattern):
        if expected is not None and text[index + offset] != expected:
            return False
    return True


def scan(load: int, text: bytes, sigs: list[Sig]) -> list[tuple[int, str, str]]:
    hits: list[tuple[int, str, str]] = []
    for index in range(0, len(text), STEP):
        for pattern, labels, version in sigs:
            end = index + len(pattern)
            if end <= len(text) and _match(text, index, pattern):
                # file_off = 0x800 + (vaddr - load), so vaddr = load + index.
                base = (load + index) & 0xFFFFFFFF
                for name, offset in labels:
                    if 0 <= offset < len(pattern):
                        hits.append(((base + offset) & 0xFFFFFFFF, name, version))
    return hits


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description="Scan a PS-X EXE for masked signatures.")
    parser.add_argument("exe", help="Path to a PS-X EXE.")
    parser.add_argument("sigs", help="Directory of signature JSON.")
    args = parser.parse_args(argv)
    try:
        load, text = read_exe(Path(args.exe))
        sigs = load_signatures(Path(args.sigs))
        hits = scan(load, text, sigs)
    except ToolError as exc:
        print(f"error: {exc}", file=sys.stderr)
        return 1
    for addr, name, version in hits:
        print(f"0x{addr:08x} {name} {version}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
