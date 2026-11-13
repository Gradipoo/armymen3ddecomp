# SPDX-License-Identifier: GPL-3.0-or-later
"""Match short patterns in a PS-X EXE text image.

Magic is the 8 bytes "PS-X EXE". PC, GP, load address, and text size are
little-endian words at 0x10, 0x14, 0x18, and 0x1C. The text starts at
file offset 0x800. file_off = 0x800 + (vaddr - load). Patterns are lines
in tools/sdk_patterns.txt. Named addresses are lines in tools/sdk_names.txt.
The scan steps 4 bytes. Each hit is one line, address then name. A named
address is printed when it sits inside the text image.

    python tools/sdk_match.py path/to/SLUS
"""

from __future__ import annotations

import argparse
import sys
from pathlib import Path

MAGIC = b"PS-X EXE"
TEXT_OFF = 0x800
STEP = 4
PATTERN_TABLE = Path(__file__).resolve().parent / "sdk_patterns.txt"
NAME_TABLE = Path(__file__).resolve().parent / "sdk_names.txt"


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


def load_patterns(path: Path) -> list[tuple[str, bytes]]:
    if not path.is_file():
        raise ToolError(f"file not found: {path}")
    try:
        text = path.read_text(encoding="utf-8")
    except UnicodeDecodeError:
        raise ToolError(f"pattern table is not utf-8: {path}") from None
    patterns: list[tuple[str, bytes]] = []
    for lineno, raw in enumerate(text.splitlines(), 1):
        line = raw.split("#", 1)[0].strip()
        if not line:
            continue
        parts = line.split()
        if len(parts) < 2:
            raise ToolError(f"bad pattern on line {lineno}")
        name = parts[0]
        try:
            blob = bytes.fromhex("".join(parts[1:]))
        except ValueError:
            raise ToolError(f"bad pattern on line {lineno}") from None
        if not blob:
            raise ToolError(f"bad pattern on line {lineno}")
        patterns.append((name, blob))
    if not patterns:
        raise ToolError("pattern table is empty")
    return patterns


def load_names(path: Path) -> list[tuple[int, str]]:
    if not path.is_file():
        raise ToolError(f"file not found: {path}")
    try:
        text = path.read_text(encoding="utf-8")
    except UnicodeDecodeError:
        raise ToolError(f"name table is not utf-8: {path}") from None
    rows: list[tuple[int, str]] = []
    for lineno, raw in enumerate(text.splitlines(), 1):
        line = raw.split("#", 1)[0].strip()
        if not line:
            continue
        parts = line.split()
        if len(parts) != 2 or not parts[0].startswith("0x"):
            raise ToolError(f"bad name on line {lineno}")
        try:
            addr = int(parts[0], 16)
        except ValueError:
            raise ToolError(f"bad name on line {lineno}") from None
        rows.append((addr & 0xFFFFFFFF, parts[1]))
    if not rows:
        raise ToolError("name table is empty")
    return rows


def names_in_text(load: int, text: bytes, rows: list[tuple[int, str]]) -> list[tuple[int, str]]:
    end = (load + len(text)) & 0xFFFFFFFF
    return [(addr, name) for addr, name in rows if load <= addr < end]


def scan(load: int, text: bytes, patterns: list[tuple[str, bytes]]) -> list[tuple[int, str]]:
    hits: list[tuple[int, str]] = []
    for index in range(0, len(text), STEP):
        for name, pat in patterns:
            end = index + len(pat)
            if end <= len(text) and text[index:end] == pat:
                # file_off = 0x800 + (vaddr - load), so vaddr = load + index.
                hits.append(((load + index) & 0xFFFFFFFF, name))
    return hits


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description="Match short patterns in a PS-X EXE.")
    parser.add_argument("exe", help="Path to a PS-X EXE.")
    args = parser.parse_args(argv)
    try:
        load, text = read_exe(Path(args.exe))
        patterns = load_patterns(PATTERN_TABLE)
        hits = scan(load, text, patterns)
        hits.extend(names_in_text(load, text, load_names(NAME_TABLE)))
    except ToolError as exc:
        print(f"error: {exc}", file=sys.stderr)
        return 1
    for addr, name in hits:
        print(f"0x{addr:08x} {name}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
