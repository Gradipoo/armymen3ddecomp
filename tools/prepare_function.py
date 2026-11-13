# SPDX-License-Identifier: GPL-3.0-or-later
"""Prepare one local MIPS range with spimdisasm and m2c. Downloads nothing.

All assembly, generated C, raw code, and logs stay under build/analysis/.
A disassembly round trip checks the exporter, not reconstructed game code.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import re
import subprocess
import sys
from collections import Counter, defaultdict
from pathlib import Path

import compare
import sdk_match

ROOT = Path(__file__).resolve().parents[1]
MAX_BYTES = 64 * 4


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def calls(code: bytes, start: int, names: dict[int, list[str]]) -> list[dict]:
    found = []
    for offset in range(0, len(code), 4):
        word = int.from_bytes(code[offset:offset + 4], 'little')
        pc = start + offset
        op = word >> 26
        if op == 3:
            target = ((pc + 4) & 0xf0000000) | ((word & 0x03ffffff) << 2)
        elif op == 0 and (word & 63) == 9:
            target = None
        else:
            continue
        link = 31 if op == 3 else (word >> 11) & 31
        found.append({'address': f'0x{pc:08x}', 'kind': 'jal' if op == 3 else 'jalr',
                      'target': None if target is None else f'0x{target:08x}',
                      'sdk_names': names.get(target, []),
                      'link_register': link,
                      'return_address': f'0x{pc + 8:08x}' if link else None,
                      'delay_slot_in_range': offset + 8 <= len(code)})
    return found


def validate_range(address: int, size: int) -> None:
    if not 0 <= address <= 0xffffffff or address % 4:
        raise ValueError('address must be an aligned 32-bit virtual address')
    if not 0 < size <= MAX_BYTES or size % 4:
        raise ValueError('size must be a positive multiple of four, at most 256 bytes')


def symbol_name(name: str, address: int, counts: Counter) -> str:
    if counts[name] == 1 and re.fullmatch(r'[A-Za-z_][A-Za-z_0-9]*', name):
        return name
    return f'sdk_{address:08X}'


def assembly_bindings(assembly: str, sdk_symbols: dict[str, int], start: int, end: int) -> str:
    # Only bind external absolute references. Branch labels stay in the assembly.
    symbols = dict(sdk_symbols)
    for name, value in re.findall(r'\b((?:func|D|RO|B)_([0-9A-Fa-f]{8}))\b', assembly):
        symbols[name] = int(value, 16)
    prefix = '.set noreorder\n.set noat\n.macro nonmatching name,size\n.endm\n'
    for name, address in sorted(symbols.items()):
        if not start <= address < end and re.search(r'\b' + re.escape(name) + r'\b', assembly):
            prefix += f'.equ {name}, 0x{address:08x}\n'
    return prefix + assembly


def run(args: argparse.Namespace) -> Path:
    validate_range(args.address, args.size)
    out = ROOT / 'build' / 'analysis' / 'functions' / f'{args.address:08x}'
    out.mkdir(parents=True, exist_ok=True)
    manifest = out / 'task.json'
    manifest.unlink(missing_ok=True)
    # Failed preparation must not leave an old draft looking like fresh output.
    draft = out / 'draft.c'
    draft.unlink(missing_ok=True)
    exe = args.exe.read_bytes()
    code = compare.reference(exe, args.address, args.size)
    load, text = sdk_match.read_exe(args.exe)
    known = sdk_match.scan(load, text, sdk_match.load_patterns(sdk_match.PATTERN_TABLE))
    known += sdk_match.names_in_text(load, text, sdk_match.load_names(sdk_match.NAME_TABLE))
    names = defaultdict(list)
    for address, name in known:
        if name not in names[address]: names[address].append(name)
    if any(args.address <= address < args.address + args.size for address in names):
        raise ValueError('named SDK entry in this range; record its call and arguments instead of preparing its body')
    if not args.python.is_file():
        raise ValueError('analysis Python not found; see docs/ANALYSIS.md for local setup')
    # Resolving a venv's Python symlink would select the base environment.
    python = str(args.python.absolute())
    raw = out / 'code.bin'
    raw.write_bytes(code)
    call_list = calls(code, args.address, names)
    counts = Counter(name for group in names.values() for name in group)
    symbols = {}
    for call in call_list:
        if call['sdk_names']:
            address = int(call['target'], 16)
            symbols[symbol_name(call['sdk_names'][0], address, counts)] = address
    csv = out / 'functions.csv'
    csv.write_text(''.join(f'{value:08X},{name}\n' for name, value in sorted(symbols.items())), encoding='utf-8')
    disasm_dir = out / 'disasm'
    disasm_dir.mkdir(exist_ok=True)
    for path in disasm_dir.glob('*.s'): path.unlink()
    command = [python, '-m', 'spimdisasm', 'singleFileDisasm', str(raw), str(disasm_dir),
        '--vram', hex(args.address), '--endian', 'little', '--arch-level', 'MIPS1',
        '--instr-category', 'r3000gte', '--compiler', 'PSYQ', '--no-nuke-pointers',
        '--no-write-binary', '--no-libultra-syms', '--no-ique-syms', '--no-hardware-regs',
        '--no-asm-comments', '--no-asm-prelude-use-includes',
        '--no-asm-prelude-use-instruction-directives', '--asm-text-label', '.globl',
        '--asm-func-as-label', '--asm-ent-label', '.ent', '--asm-end-label', '.end',
        '--functions', str(csv)]
    commands = [command]
    with (out / 'disassembler.log').open('wb') as log:
        subprocess.run(command, stdout=log, stderr=log, cwd=out, check=True)
    files = list(disasm_dir.glob('*.s'))
    if len(files) != 1:
        raise ValueError('expected one assembly file; inspect the local disassembler log')
    m2c = [python, '-c', 'from m2c.main import main; main()', '-t', 'mipsel-gcc-c',
           '--no-cache', '--globals', 'none']
    context_hash = None
    if args.context:
        context = args.context.read_bytes()
        local_context = out / 'context.h'
        local_context.write_bytes(context)
        context_hash = digest(context)
        m2c += ['--context', str(local_context)]
    m2c.append(str(files[0]))
    commands.append(m2c)
    with draft.open('wb') as stdout, (out / 'decompiler.log').open('wb') as log:
        result = subprocess.run(m2c, stdout=stdout, stderr=log, cwd=out)
    if result.returncode:
        draft.rename(out / 'failed-draft.txt')
        raise ValueError('m2c could not draft this range; inspect the local decompiler log')
    roundtrip = None
    if args.llvm_mc:
        assembly = assembly_bindings(files[0].read_text(), symbols, args.address, args.address + args.size)
        reference = out / 'reference.s'
        reference.write_text(assembly, encoding='utf-8')
        obj = out / 'reference.o'
        assembler = [str(args.llvm_mc.resolve()), '-triple=mipsel-none-elf', '-mcpu=mips1',
                     '-filetype=obj', str(reference), '-o', str(obj)]
        commands.append(assembler)
        with (out / 'roundtrip.log').open('wb') as log:
            subprocess.run(assembler, stdout=log, stderr=log, cwd=out, check=True)
        roundtrip = compare.elf_section(obj.read_bytes(), '.text') == code
        if not roundtrip: raise ValueError('disassembly round trip differs; no code was trimmed or masked')
    query = 'import importlib.metadata as m,json; print(json.dumps({n:m.version(n) for n in ("spimdisasm","m2c","rabbitizer","splat64")}))'
    versions = json.loads(subprocess.check_output([python, '-c', query], cwd=out, text=True))
    record = {'address': hex(args.address), 'size': args.size, 'calls': call_list,
        'static_range_only': True, 'notes_must_follow_AGENTS': True,
        'exe_sha256': digest(exe), 'code_sha256': digest(code), 'context_sha256': context_hash,
        'sdk_names_sha256': digest(sdk_match.NAME_TABLE.read_bytes()),
        'sdk_patterns_sha256': digest(sdk_match.PATTERN_TABLE.read_bytes()),
        'tool_versions': versions, 'commands': commands, 'draft_sha256': digest(draft.read_bytes()),
        'disassembly_roundtrip_exact': roundtrip,
        'warning': 'A C draft and a disassembly round trip do not verify a reconstructed implementation.'}
    manifest.write_text(json.dumps(record, indent=2) + '\n', encoding='utf-8')
    return out


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('exe', type=Path)
    parser.add_argument('--address', type=lambda s: int(s, 0), required=True)
    parser.add_argument('--size', type=lambda s: int(s, 0), required=True,
                        help='Reviewed contiguous byte count, not an inferred Ghidra body size')
    default_python = ROOT / 'build' / 'analysis' / 'venv' / ('Scripts/python.exe' if sys.platform == 'win32' else 'bin/python')
    parser.add_argument('--python', type=Path, default=default_python)
    parser.add_argument('--context', type=Path, help='Preprocessed C declarations for m2c')
    parser.add_argument('--llvm-mc', type=Path, help='Optionally check the disassembly round trip')
    args = parser.parse_args(argv)
    args.exe = args.exe.resolve()
    try:
        out = run(args)
    except (OSError, ValueError, subprocess.CalledProcessError) as exc:
        print(f'error: {exc}', file=sys.stderr)
        return 1
    print(f'Prepared local range: {out}')
    print('Generated C stays local. Review the draft and call metadata before writing our code.')
    return 0


if __name__ == '__main__':
    sys.exit(main())
