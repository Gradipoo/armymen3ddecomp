# SPDX-License-Identifier: GPL-3.0-or-later
"""Disassemble the first four MIPS instructions at a PS-X EXE entry.

Reads the header the same way tools/exe_info.py does. Magic is the 8 bytes
"PS-X EXE". PC, GP, load address, and text size are little-endian words at
0x10, 0x14, 0x18, and 0x1C. The text starts at file offset 0x800. The entry
file offset is 0x800 + (pc - load). For the recorded USA header that offset
is 0x701f8. Writes four lines to build/entry-disasm.txt under the repo root.
That file stays in build/ and is not committed.

    python tools/entry_disasm.py path/to/SLUS
"""

from __future__ import annotations

import argparse
import sys
from pathlib import Path

MAGIC = b"PS-X EXE"
TEXT_OFFSET = 0x800
ENTRY_COUNT = 4
ROOT = Path(__file__).resolve().parent.parent
OUT_PATH = ROOT / "build" / "entry-disasm.txt"

REGS = (
    "zero", "at", "v0", "v1", "a0", "a1", "a2", "a3",
    "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
    "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",
    "t8", "t9", "k0", "k1", "gp", "sp", "fp", "ra",
)

# funct field for opcode 0. Value is (mnemonic, operand shape).
# Shapes: shift, jr, jalr, hi, lo, mult, alu, word.
SPECIAL = {
    0x00: ("sll", "shift"),
    0x02: ("srl", "shift"),
    0x03: ("sra", "shift"),
    0x04: ("sllv", "shiftv"),
    0x06: ("srlv", "shiftv"),
    0x07: ("srav", "shiftv"),
    0x08: ("jr", "jr"),
    0x09: ("jalr", "jalr"),
    0x0C: ("syscall", "bare"),
    0x0D: ("break", "bare"),
    0x10: ("mfhi", "from"),
    0x11: ("mthi", "to"),
    0x12: ("mflo", "from"),
    0x13: ("mtlo", "to"),
    0x18: ("mult", "mult"),
    0x19: ("multu", "mult"),
    0x1A: ("div", "mult"),
    0x1B: ("divu", "mult"),
    0x20: ("add", "alu"),
    0x21: ("addu", "alu"),
    0x22: ("sub", "alu"),
    0x23: ("subu", "alu"),
    0x24: ("and", "alu"),
    0x25: ("or", "alu"),
    0x26: ("xor", "alu"),
    0x27: ("nor", "alu"),
    0x2A: ("slt", "alu"),
    0x2B: ("sltu", "alu"),
}

LOADS = {
    0x20: "lb",
    0x21: "lh",
    0x22: "lwl",
    0x23: "lw",
    0x24: "lbu",
    0x25: "lhu",
    0x26: "lwr",
    0x28: "sb",
    0x29: "sh",
    0x2A: "swl",
    0x2B: "sw",
    0x2E: "swr",
}


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


def entry_offset(pc: int, load: int, size: int) -> int:
    if pc < load:
        raise ToolError("entry pc is below the load address")
    offset = TEXT_OFFSET + (pc - load)
    end = offset + ENTRY_COUNT * 4
    text_end = TEXT_OFFSET + size
    if end > text_end:
        raise ToolError("entry is outside the text section")
    return offset


def _reg(number: int) -> str:
    return REGS[number]


def _simm(imm: int) -> str:
    signed = imm - 0x10000 if imm & 0x8000 else imm
    if signed < 0:
        return f"-0x{-signed:x}"
    return f"0x{signed:x}"


def _word(value: int) -> str:
    return f".word 0x{value:08x}"


def _special(word: int, rs: int, rt: int, rd: int, sa: int, funct: int) -> str:
    if word == 0:
        return "nop"
    found = SPECIAL.get(funct)
    if found is None:
        return _word(word)
    name, shape = found
    if shape == "shift":
        return f"{name} {_reg(rd)}, {_reg(rt)}, {sa}"
    if shape == "shiftv":
        return f"{name} {_reg(rd)}, {_reg(rt)}, {_reg(rs)}"
    if shape == "jr":
        return f"{name} {_reg(rs)}"
    if shape == "jalr":
        if rd == 31:
            return f"{name} {_reg(rs)}"
        return f"{name} {_reg(rd)}, {_reg(rs)}"
    if shape == "from":
        return f"{name} {_reg(rd)}"
    if shape == "to":
        return f"{name} {_reg(rs)}"
    if shape == "mult":
        return f"{name} {_reg(rs)}, {_reg(rt)}"
    if shape == "alu":
        return f"{name} {_reg(rd)}, {_reg(rs)}, {_reg(rt)}"
    return name


def _branch(addr: int, op: str, left: str, right: str | None, imm: int) -> str:
    target = addr + 4 + ((_simm_value(imm)) << 2)
    dest = f"0x{target:08x}"
    if right is None:
        return f"{op} {left}, {dest}"
    return f"{op} {left}, {right}, {dest}"


def _simm_value(imm: int) -> int:
    return imm - 0x10000 if imm & 0x8000 else imm


def decode(word: int, addr: int) -> str:
    op = (word >> 26) & 0x3F
    rs = (word >> 21) & 0x1F
    rt = (word >> 16) & 0x1F
    rd = (word >> 11) & 0x1F
    sa = (word >> 6) & 0x1F
    funct = word & 0x3F
    imm = word & 0xFFFF
    if op == 0x00:
        return _special(word, rs, rt, rd, sa, funct)
    if op == 0x01:
        if rt == 0x00:
            return _branch(addr, "bltz", _reg(rs), None, imm)
        if rt == 0x01:
            return _branch(addr, "bgez", _reg(rs), None, imm)
        if rt == 0x10:
            return _branch(addr, "bltzal", _reg(rs), None, imm)
        if rt == 0x11:
            return _branch(addr, "bgezal", _reg(rs), None, imm)
        return _word(word)
    if op == 0x02:
        return f"j 0x{_jump_target(addr, word):08x}"
    if op == 0x03:
        return f"jal 0x{_jump_target(addr, word):08x}"
    if op == 0x04:
        return _branch(addr, "beq", _reg(rs), _reg(rt), imm)
    if op == 0x05:
        return _branch(addr, "bne", _reg(rs), _reg(rt), imm)
    if op == 0x06:
        return _branch(addr, "blez", _reg(rs), None, imm)
    if op == 0x07:
        return _branch(addr, "bgtz", _reg(rs), None, imm)
    if op in (0x08, 0x09, 0x0A, 0x0B):
        name = {0x08: "addi", 0x09: "addiu", 0x0A: "slti", 0x0B: "sltiu"}[op]
        return f"{name} {_reg(rt)}, {_reg(rs)}, {_simm(imm)}"
    if op in (0x0C, 0x0D, 0x0E):
        name = {0x0C: "andi", 0x0D: "ori", 0x0E: "xori"}[op]
        return f"{name} {_reg(rt)}, {_reg(rs)}, 0x{imm:x}"
    if op == 0x0F:
        return f"lui {_reg(rt)}, 0x{imm:x}"
    if op == 0x10 and rs == 0x00:
        return f"mfc0 {_reg(rt)}, {_reg(rd)}"
    if op == 0x10 and rs == 0x04:
        return f"mtc0 {_reg(rt)}, {_reg(rd)}"
    if op == 0x10 and rs & 0x10 and funct == 0x10:
        return "rfe"
    if op in LOADS:
        return f"{LOADS[op]} {_reg(rt)}, {_simm(imm)}({_reg(rs)})"
    return _word(word)


def _jump_target(addr: int, word: int) -> int:
    return ((addr + 4) & 0xF0000000) | ((word & 0x03FFFFFF) << 2)


def read_entry(path: Path, offset: int) -> list[int]:
    with path.open("rb") as handle:
        handle.seek(offset)
        blob = handle.read(ENTRY_COUNT * 4)
    if len(blob) < ENTRY_COUNT * 4:
        raise ToolError("PS-X EXE text is truncated")
    return [int.from_bytes(blob[i:i + 4], "little") for i in range(0, ENTRY_COUNT * 4, 4)]


def format_entry(pc: int, words: list[int]) -> str:
    lines = []
    for index, word in enumerate(words):
        addr = pc + index * 4
        lines.append(f"0x{addr:08x}  {decode(word, addr)}")
    return "\n".join(lines) + "\n"


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        description="Disassemble the first four MIPS instructions at a PS-X EXE entry."
    )
    parser.add_argument("exe", help="Path to a PS-X EXE.")
    args = parser.parse_args(argv)
    try:
        path = Path(args.exe)
        pc, _gp, load, size = read_header(path)
        offset = entry_offset(pc, load, size)
        text = format_entry(pc, read_entry(path, offset))
        OUT_PATH.parent.mkdir(parents=True, exist_ok=True)
        OUT_PATH.write_text(text, encoding="utf-8")
    except ToolError as exc:
        print(f"error: {exc}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
