# SPDX-License-Identifier: GPL-3.0-or-later
"""Slice one boot note from a PS-X EXE.

Follows the note rule in AGENTS.md. From --start, walk this boot until
jr, the first jal or jalr whose target is not already named, or 64
instructions, whichever comes first. A target is named when tools/sdk_names.txt
or a tools/sdk_patterns.txt hit names it, when it is BIOS A, B, or C
(0xa0, 0xb0, 0xc0), or when docs/research/re/call-ADDRESS.md already exists.
A named call records the name, the immediate arguments, and the return
address, then continues at that return. It does not enter the body.
A conditional branch is followed when its inputs are known. An unknown
branch stops. The taken side is not guessed in that case.
A word store of a known value is remembered. A later word load of that
address reuses it. A load of any other address stays unknown. File
bytes are not live memory: a fill can leave a zero where the
executable still holds the original word. word_fill and bzero hide
their range. Other skipped calls leave stored words in place. A store
through an unknown address does not wipe the map.
The default cap is 64 instructions, one note. --max raises that cap
for this local report only. --ra is the ra value on entry. A later
save and reload through sp returns that value.
An unnamed call whose target is inside this executable is entered, up
to 8 calls deep. jr back to that call's return address resumes the
caller. A named call is not entered.
Unconditional j is followed. A jump back into this slice stops.
The cap is checked before each new instruction. A delay slot is still
included, so a stop on instruction 64 can report 65 lines.

Writes build/boot-slice.txt. That file stays in build/ and is not committed.

    python tools/boot_slice.py path/to/SLUS --start 0x8007e130
"""

from __future__ import annotations

import argparse
import importlib.util
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
OUT_PATH = ROOT / "build" / "boot-slice.txt"
NOTES = ROOT / "docs" / "research" / "re"
MAX_INSTRUCTIONS = 64
MAX_CALLS = 8
BIOS = {0xA0: "BIOS-A", 0xB0: "BIOS-B", 0xC0: "BIOS-C"}
VOLATILE = (1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 24, 25)


def _load(stem: str):
    path = Path(__file__).resolve().parent / f"{stem}.py"
    spec = importlib.util.spec_from_file_location(f"am3d_{stem}", path)
    module = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = module
    spec.loader.exec_module(module)
    return module


DISASM = _load("entry_disasm")
SDK = _load("sdk_match")


class ToolError(Exception):
    pass


def _fmt(value: int) -> str:
    return f"0x{value & 0xFFFFFFFF:08x}"


def _read_word(text: bytes, load: int, addr: int) -> int:
    if addr < load or (addr - load) % 4 != 0:
        raise ToolError(f"address is outside the text section: 0x{addr:08x}")
    offset = addr - load
    if offset + 4 > len(text):
        raise ToolError(f"address is outside the text section: 0x{addr:08x}")
    return int.from_bytes(text[offset:offset + 4], "little")


def _in_text(text: bytes, load: int, addr: int) -> bool:
    if addr < load or (addr - load) % 4 != 0:
        return False
    return (addr - load) + 4 <= len(text)


def _classify(word: int, addr: int, regs: dict[int, int]):
    op = (word >> 26) & 0x3F
    rs = (word >> 21) & 0x1F
    funct = word & 0x3F
    if op == 0x00 and funct == 0x08:
        return "jr", rs, regs.get(rs)
    if op == 0x00 and funct == 0x09:
        return "jalr", rs, regs.get(rs)
    if op == 0x02:
        return "j", None, DISASM._jump_target(addr, word)
    if op == 0x03:
        return "jal", None, DISASM._jump_target(addr, word)
    if op in (0x01, 0x04, 0x05, 0x06, 0x07):
        return "branch", None, None
    if op in (0x10, 0x11, 0x12) and rs == 0x08:
        return "branch", None, None
    return "normal", None, None


def _known(regs: dict[int, int], reg: int):
    if reg == 0:
        return 0
    return regs.get(reg)


def _write(regs: dict[int, int], reg: int, value, origins=None, origin="imm"):
    if reg == 0:
        return
    if value is None:
        regs.pop(reg, None)
        if origins is not None:
            origins.pop(reg, None)
    else:
        regs[reg] = value & 0xFFFFFFFF
        if origins is not None:
            origins[reg] = origin


def _clear_volatile(regs: dict[int, int], origins=None) -> None:
    for reg in VOLATILE:
        regs.pop(reg, None)
        if origins is not None:
            origins.pop(reg, None)


def _mem_addr(regs: dict[int, int], rs: int, simm: int):
    base = _known(regs, rs)
    if base is None:
        return None
    return (base + simm) & 0xFFFFFFFF


class Frame:
    def __init__(self):
        self.delta = 0

    def move(self, simm: int) -> None:
        if self.delta is None:
            return
        self.delta = (self.delta + simm) & 0xFFFFFFFF

    def lose(self) -> None:
        self.delta = None


class Words:
    def __init__(self):
        self.values: dict[int, int] = {}

    def block(self, start, size) -> None:
        if start is None or size is None:
            self.values.clear()
            return
        size &= 0xFFFFFFFF
        if size == 0:
            return
        end = (start + size) & 0xFFFFFFFF
        if end <= start:
            self.values.clear()
            return
        for addr in list(self.values):
            if addr < end and start < addr + 4:
                del self.values[addr]

    def store_word(self, addr, value) -> None:
        if addr is None:
            return
        if addr % 4:
            self.block(addr, 4)
            return
        if value is None:
            self.values.pop(addr, None)
            return
        self.values[addr] = value & 0xFFFFFFFF

    def load_word(self, addr):
        if addr is None or addr % 4:
            return None, None
        if addr in self.values:
            return self.values[addr], "mem"
        return None, None


def _one(origins: dict[int, str], reg: int) -> str:
    if reg == 0:
        return "imm"
    return origins.get(reg, "imm")


def _mix(origins: dict[int, str], left: int, right: int) -> str:
    kinds = (_one(origins, left), _one(origins, right))
    if "mem" in kinds:
        return "mem"
    if "header" in kinds:
        return "header"
    return "imm"


def _stack_store(regs, origins, frame: Frame, stack, rt, simm) -> None:
    slot = (frame.delta + simm) & 0xFFFFFFFF
    value = _known(regs, rt)
    if value is None:
        stack.pop(slot, None)
        return
    stack[slot] = (value, _one(origins, rt))


def _store_word(regs, words: Words, rs, rt, simm) -> None:
    words.store_word(_mem_addr(regs, rs, simm), _known(regs, rt))


def _apply(
    word: int,
    regs: dict[int, int],
    words: Words,
    origins: dict[int, str],
    frame: Frame,
    stack: dict[int, tuple[int, str]],
) -> None:
    def put(reg: int, value, origin="imm"):
        if reg == 29:
            frame.lose()
        _write(regs, reg, value, origins, origin)
    op = (word >> 26) & 0x3F
    rs = (word >> 21) & 0x1F
    rt = (word >> 16) & 0x1F
    rd = (word >> 11) & 0x1F
    sa = (word >> 6) & 0x1F
    funct = word & 0x3F
    imm = word & 0xFFFF
    simm = imm - 0x10000 if imm & 0x8000 else imm

    if word == 0 or op in (0x02, 0x03, 0x04, 0x05, 0x06, 0x07):
        return
    if op == 0x01:
        return
    if op == 0x00:
        if funct in (0x08, 0x18, 0x19, 0x1A, 0x1B, 0x0C, 0x0D):
            return
        if funct == 0x09:
            put(rd, None)
            return
        if funct in (0x10, 0x12):
            put(rd, None)
            return
        if funct in (0x11, 0x13):
            return
        left = _known(regs, rt)
        if funct in (0x00, 0x02, 0x03):
            origin = _one(origins, rt)
            if left is None:
                put(rd, None)
            elif funct == 0x00:
                put(rd, left << sa, origin)
            elif funct == 0x02:
                put(rd, (left & 0xFFFFFFFF) >> sa, origin)
            else:
                put(rd, (left - 0x100000000 if left & 0x80000000 else left) >> sa, origin)
            return
        right = _known(regs, rs)
        if funct in (0x04, 0x06, 0x07):
            shift = _known(regs, rs)
            origin = _one(origins, rt)
            if left is None or shift is None:
                put(rd, None)
            elif funct == 0x04:
                put(rd, left << (shift & 0x1F), origin)
            elif funct == 0x06:
                put(rd, (left & 0xFFFFFFFF) >> (shift & 0x1F), origin)
            else:
                signed = left - 0x100000000 if left & 0x80000000 else left
                put(rd, signed >> (shift & 0x1F), origin)
            return
        if right is None or left is None:
            put(rd, None)
            return
        if funct == 0x20 or funct == 0x21:
            put(rd, right + left, _mix(origins, rs, rt))
        elif funct == 0x22 or funct == 0x23:
            put(rd, right - left, _mix(origins, rs, rt))
        elif funct == 0x24:
            put(rd, right & left, _mix(origins, rs, rt))
        elif funct == 0x25:
            put(rd, right | left, _mix(origins, rs, rt))
        elif funct == 0x26:
            put(rd, right ^ left, _mix(origins, rs, rt))
        elif funct == 0x27:
            put(rd, ~(right | left), _mix(origins, rs, rt))
        elif funct == 0x2A:
            put(rd, 1 if _signed(right) < _signed(left) else 0, _mix(origins, rs, rt))
        elif funct == 0x2B:
            put(rd, 1 if (right & 0xFFFFFFFF) < (left & 0xFFFFFFFF) else 0, _mix(origins, rs, rt))
        else:
            _clear_volatile(regs, origins)
        return
    if op in (0x08, 0x09):
        if rt == 29 and rs == 29 and frame.delta is not None:
            frame.move(simm)
            return
        base = _known(regs, rs)
        put(rt, None if base is None else base + simm, _one(origins, rs))
        return
    if op in (0x0C, 0x0D, 0x0E):
        base = _known(regs, rs)
        if base is None:
            put(rt, None)
        elif op == 0x0C:
            put(rt, base & imm, _one(origins, rs))
        elif op == 0x0D:
            put(rt, base | imm, _one(origins, rs))
        else:
            put(rt, base ^ imm, _one(origins, rs))
        return
    if op == 0x0F:
        put(rt, imm << 16)
        return
    if op == 0x2B:
        if rs == 29 and frame.delta is not None:
            _stack_store(regs, origins, frame, stack, rt, simm)
            return
        _store_word(regs, words, rs, rt, simm)
        return
    if op in (0x28, 0x29, 0x2A, 0x2E):
        width = 1 if op == 0x28 else 2 if op == 0x29 else 4
        addr = _mem_addr(regs, rs, simm)
        if addr is not None:
            words.block(addr, width)
        return
    if op == 0x23:
        if rs == 29 and frame.delta is not None:
            found = stack.get((frame.delta + simm) & 0xFFFFFFFF)
            if found is None:
                put(rt, None)
            else:
                put(rt, found[0], found[1])
            return
        value, origin = words.load_word(_mem_addr(regs, rs, simm))
        put(rt, value, origin or "imm")
        return
    if op in (0x20, 0x21, 0x22, 0x24, 0x25, 0x26):
        put(rt, None)
        return
    if op == 0x10 and rs == 0x00:
        put(rt, None)
        return
    if op == 0x10 and rs == 0x04:
        return
    _clear_volatile(regs, origins)


def _signed(value: int) -> int:
    value &= 0xFFFFFFFF
    return value - 0x100000000 if value & 0x80000000 else value


def _branch_target(pc: int, word: int) -> int:
    imm = word & 0xFFFF
    simm = imm - 0x10000 if imm & 0x8000 else imm
    return (pc + 4 + (simm << 2)) & 0xFFFFFFFF


def _branch_goes(word: int, regs: dict[int, int]):
    op = (word >> 26) & 0x3F
    rs = (word >> 21) & 0x1F
    rt = (word >> 16) & 0x1F
    left = _known(regs, rs)
    if op in (0x01, 0x06, 0x07):
        if left is None:
            return None
        signed = _signed(left)
        if op == 0x06:
            return signed <= 0
        if op == 0x07:
            return signed > 0
        if rt in (0x00, 0x10):
            return signed < 0
        if rt in (0x01, 0x11):
            return signed >= 0
        return None
    if op in (0x04, 0x05):
        right = _known(regs, rt)
        if left is None or right is None:
            return None
        same = (left & 0xFFFFFFFF) == (right & 0xFFFFFFFF)
        return same if op == 0x04 else not same
    return None


def _pattern_name(text: bytes, load: int, addr: int, patterns) -> str | None:
    if not _in_text(text, load, addr):
        return None
    blob = text[addr - load:]
    best = None
    best_len = -1
    for name, pattern in patterns:
        if blob.startswith(pattern) and len(pattern) > best_len:
            best = name
            best_len = len(pattern)
    return best


def _lookup(text, load, addr, names, patterns, notes_dir):
    if addr is None:
        return None, None
    if addr in names:
        return names[addr], "sdk"
    pattern = _pattern_name(text, load, addr, patterns)
    if pattern is not None:
        return pattern, "pattern"
    if addr in BIOS:
        return BIOS[addr], "bios"
    note = notes_dir / f"call-{addr:08x}.md"
    if note.is_file():
        return "noted", "note"
    return None, None


def _args(regs: dict[int, int], origins: dict[int, str]) -> str:
    parts = []
    for reg, name in ((4, "a0"), (5, "a1"), (6, "a2"), (7, "a3")):
        value = _known(regs, reg)
        if value is not None:
            kind = origins.get(reg)
            mark = f" {kind}" if kind in ("mem", "header") else ""
            parts.append(f"{name}={_fmt(value)}{mark}")
    if not parts:
        return "args unknown"
    return "args " + " ".join(parts)


def slice_text(
    text: bytes,
    load: int,
    start: int,
    names,
    patterns,
    notes_dir: Path,
    limit: int = MAX_INSTRUCTIONS,
    gp: int | None = None,
    ra: int | None = None,
) -> str:
    if limit < 1:
        raise ToolError("instruction cap is below 1")
    if not _in_text(text, load, start):
        raise ToolError(f"address is outside the text section: 0x{start:08x}")
    regs: dict[int, int] = {0: 0}
    origins: dict[int, str] = {}
    if gp is not None:
        regs[28] = gp & 0xFFFFFFFF
        origins[28] = "header"
    if ra is not None:
        regs[31] = ra & 0xFFFFFFFF
    words = Words()
    frame = Frame()
    stack: dict[int, tuple[int, str]] = {}
    returns: list[dict] = []
    lines: list[str] = []
    calls: list[str] = []
    branches: list[str] = []
    stop = None
    nxt = None
    pc = start
    seen: set[int] = set()

    while stop is None:
        if len(lines) >= limit:
            stop = "cap"
            nxt = f"0x{pc:08x}"
            break
        if pc in seen:
            stop = "loop"
            nxt = f"0x{pc:08x}"
            break
        if not _in_text(text, load, pc):
            stop = "end"
            nxt = f"0x{pc:08x}"
            break
        word = _read_word(text, load, pc)
        kind, reg, target = _classify(word, pc, regs)
        if kind == "normal":
            seen.add(pc)
            lines.append(f"0x{pc:08x}  {DISASM.decode(word, pc)}")
            _apply(word, regs, words, origins, frame, stack)
            pc += 4
            continue
        if not _in_text(text, load, pc + 4):
            raise ToolError(f"delay slot is outside the text section: 0x{pc + 4:08x}")
        goes = _branch_goes(word, regs) if kind == "branch" else None
        seen.add(pc)
        lines.append(f"0x{pc:08x}  {DISASM.decode(word, pc)}")
        _apply(word, regs, words, origins, frame, stack)
        if kind in ("jal", "jalr"):
            _write(regs, 31, pc + 8, origins)
        if (
            kind == "branch"
            and ((word >> 26) & 0x3F) == 0x01
            and ((word >> 16) & 0x1F) in (0x10, 0x11)
        ):
            _write(regs, 31, pc + 8, origins)
        delay_word = _read_word(text, load, pc + 4)
        seen.add(pc + 4)
        lines.append(f"0x{pc + 4:08x}  {DISASM.decode(delay_word, pc + 4)}")
        _apply(delay_word, regs, words, origins, frame, stack)
        if kind == "branch":
            taken = _branch_target(pc, word)
            fall = (pc + 8) & 0xFFFFFFFF
            if goes is None:
                stop = "branch"
                branches.append(
                    f"branch 0x{pc:08x} taken 0x{taken:08x} fall 0x{fall:08x}"
                )
                nxt = "unknown"
                break
            dest = taken if goes else fall
            side = "taken" if goes else "fall"
            branches.append(f"branch 0x{pc:08x} {side} 0x{dest:08x}")
            if not _in_text(text, load, dest):
                stop = "branch-out"
                nxt = f"0x{dest:08x}"
                break
            pc = dest
            continue
        if kind == "jr":
            dest = _known(regs, reg)
            if returns and dest == returns[-1]["pc"]:
                saved = returns.pop()
                frame.delta = saved["delta"]
                stack.clear()
                stack.update(saved["slots"])
                calls.append(f"return {_fmt(dest)}")
                pc = dest
                continue
            stop = "jr"
            if dest is not None:
                nxt = _fmt(dest)
            elif reg == 31:
                nxt = "ra"
            else:
                nxt = "unknown"
            break
        if kind == "j":
            if not _in_text(text, load, target):
                stop = "j-out"
                nxt = f"0x{target:08x}"
                break
            pc = target
            continue
        label, source = _lookup(text, load, target, names, patterns, notes_dir)
        goal = f"0x{target:08x}" if target is not None else "unknown"
        call = f"call 0x{pc:08x} {kind} {goal}"
        if label is None:
            call += " unnamed"
        else:
            call += f" {label} {source}"
        if label == "BIOS-A" or label == "BIOS-B" or label == "BIOS-C":
            number = _known(regs, 9)
            if number is not None:
                call += f" t1={_fmt(number)}"
        calls.append(call)
        calls.append(_args(regs, origins))
        calls.append(f"ra 0x{pc + 8:08x}")
        if label is None:
            ret = (pc + 8) & 0xFFFFFFFF
            can_enter = (
                target is not None
                and _in_text(text, load, target)
                and target not in seen
                and len(returns) < MAX_CALLS
            )
            if can_enter:
                returns.append({
                    "pc": ret,
                    "delta": frame.delta,
                    "slots": dict(stack),
                })
                frame.delta = 0
                stack.clear()
                for reg in VOLATILE:
                    if reg not in (4, 5, 6, 7):
                        regs.pop(reg, None)
                        origins.pop(reg, None)
                _write(regs, 31, ret, origins)
                pc = target
                continue
            stop = "unnamed-jal" if kind == "jal" else "unnamed-jalr"
            nxt = goal if target is not None else "unknown"
            break
        if label in ("word_fill", "bzero"):
            length_reg = 6 if label == "word_fill" else 5
            words.block(_known(regs, 4), _known(regs, length_reg))
        _clear_volatile(regs, origins)
        _write(regs, 31, pc + 8, origins)
        pc = pc + 8

    out = [f"start 0x{start:08x}", f"count {len(lines)}"]
    out.extend(lines)
    out.append(f"stop {stop}")
    out.extend(branches)
    out.extend(calls)
    out.append(f"next {nxt}")
    return "\n".join(out) + "\n"


def _parse_max(text: str) -> int:
    try:
        value = int(text, 0)
    except ValueError as exc:
        raise argparse.ArgumentTypeError("max must be an integer") from exc
    if value < 1 or value > 4096:
        raise argparse.ArgumentTypeError("max must be from 1 to 4096")
    return value


def _parse_start(text: str) -> int:
    try:
        value = int(text, 0)
    except ValueError as exc:
        raise argparse.ArgumentTypeError("start address must be an integer") from exc
    if value < 0 or value > 0xFFFFFFFF:
        raise argparse.ArgumentTypeError("start address is out of range")
    return value


def main(argv: list[str] | None = None, out_path: Path | None = None) -> int:
    parser = argparse.ArgumentParser(description="Slice one boot note from a PS-X EXE.")
    parser.add_argument("exe", help="Path to a PS-X EXE.")
    parser.add_argument("--start", type=_parse_start, required=True, help="Virtual address.")
    parser.add_argument("--notes", type=Path, default=NOTES, help="Directory of call notes.")
    parser.add_argument(
        "--max",
        type=_parse_max,
        default=MAX_INSTRUCTIONS,
        help="Instruction cap for this local report. Default: 64.",
    )
    parser.add_argument(
        "--ra",
        type=_parse_start,
        help="Value of ra on entry. A save and reload through sp keeps it.",
    )
    args = parser.parse_args(argv)
    dest = OUT_PATH if out_path is None else out_path
    try:
        _pc, gp, _load, _size = DISASM.read_header(Path(args.exe))
        load, text = SDK.read_exe(Path(args.exe))
        names = {addr: name for addr, name in SDK.load_names(SDK.NAME_TABLE)}
        patterns = SDK.load_patterns(SDK.PATTERN_TABLE)
        report = slice_text(
            text, load, args.start, names, patterns, args.notes, args.max, gp, args.ra
        )
        dest.parent.mkdir(parents=True, exist_ok=True)
        dest.write_text(report, encoding="utf-8")
    except (ToolError, SDK.ToolError, DISASM.ToolError) as exc:
        print(f"error: {exc}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
