# SPDX-License-Identifier: GPL-3.0-or-later
"""Print the load fields from a PS-X EXE header.

Magic is the 8 bytes "PS-X EXE". PC, GP, load address, and text size are
little-endian words at 0x10, 0x14, 0x18, and 0x1C. The text starts at
file offset 0x800.

    python tools/exe_info.py path/to/SLUS
"""

from __future__ import annotations

import argparse
import sys
from pathlib import Path

MAGIC = b"PS-X EXE"


class ToolError(Exception):
    pass


def read_header(path: Path) -> tuple[int, int, int, int]:
    if not path.is_file():
        raise ToolError(f"file not found: {path}")
    with path.open("rb") as handle:
        header = handle.read(0x20)
    if len(header) < 8 or header[:8] != MAGIC:
        raise ToolError("not a PS-X EXE (bad magic)")
    if len(header) < 0x20:
        raise ToolError("PS-X EXE header is truncated")
    pc = int.from_bytes(header[0x10:0x14], "little")
    gp = int.from_bytes(header[0x14:0x18], "little")
    load = int.from_bytes(header[0x18:0x1C], "little")
    size = int.from_bytes(header[0x1C:0x20], "little")
    return pc, gp, load, size


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description="Print PC, GP, load address, and text size from a PS-X EXE.")
    parser.add_argument("exe", help="Path to a PS-X EXE.")
    args = parser.parse_args(argv)
    try:
        pc, gp, load, size = read_header(Path(args.exe))
    except ToolError as exc:
        print(f"error: {exc}", file=sys.stderr)
        return 1
    print(f"pc=0x{pc:08x}")
    print(f"gp=0x{gp:08x}")
    print(f"load=0x{load:08x}")
    print(f"text_size=0x{size:08x}")
    print("text_offset=0x800")
    return 0


if __name__ == "__main__":
    sys.exit(main())
