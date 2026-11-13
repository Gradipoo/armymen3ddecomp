# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare local candidate code with a PS-X EXE range. No relocation masking.

Accepts a raw code file or an ELF32 little-endian MIPS object section.
Detailed byte differences stay under build/compare/. This is an exact byte
check only. It neither compiles C nor proves behavior for other inputs.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def number(value: str) -> int:
    return int(value, 0)


def region(data: bytes, offset: int, size: int) -> bytes:
    if offset < 0 or size < 0 or offset + size > len(data):
        raise ValueError('file range is truncated or out of bounds')
    return data[offset:offset + size]


def elf_section(data: bytes, name: str) -> bytes:
    if len(data) < 52 or data[:7] != b'\x7fELF\x01\x01\x01':
        raise ValueError('expected ELF32 little-endian version 1')
    kind, machine, version = struct.unpack_from('<HHI', data, 16)
    if kind not in (1, 2) or machine != 8 or version != 1:
        raise ValueError('expected a MIPS relocatable object or executable')
    offset = struct.unpack_from('<I', data, 32)[0]
    header_size, count, strings = struct.unpack_from('<HHH', data, 46)
    if header_size != 40 or not count or strings >= count:
        raise ValueError('invalid or unsupported ELF section table')
    headers = [struct.unpack('<10I', region(data, offset + i * 40, 40))
               for i in range(count)]
    string_header = headers[strings]
    names = region(data, string_header[4], string_header[5])
    selected = []
    for index, header in enumerate(headers):
        start = header[0]
        end = names.find(b'\0', start)
        if start >= len(names) or end < 0:
            raise ValueError('invalid ELF section name')
        if names[start:end] == name.encode('utf-8'):
            selected.append((index, header))
    if len(selected) != 1:
        raise ValueError(f'expected exactly one section named {name}')
    index, header = selected[0]
    if header[1] != 1 or not header[2] & 4:
        raise ValueError('candidate section must contain executable PROGBITS')
    if any(h[1] in (4, 9) and h[7] == index and h[5] for h in headers):
        raise ValueError('candidate section has unresolved relocations; link it first')
    return region(data, header[4], header[5])


def reference(data: bytes, address: int, size: int) -> bytes:
    if len(data) < 0x800 or data[:8] != b'PS-X EXE':
        raise ValueError('expected a PS-X EXE with a complete header')
    load, text_size = struct.unpack_from('<II', data, 0x18)
    region(data, 0x800, text_size)
    if address % 4 or size <= 0 or size % 4:
        raise ValueError('address and positive size must be word-aligned')
    if address < load or address + size > load + text_size:
        raise ValueError('reference range is outside the EXE text image')
    return region(data, 0x800 + address - load, size)


def compare(expected: bytes, actual: bytes, address: int) -> dict:
    if len(expected) != len(actual):
        raise ValueError('candidate size differs from requested range; no padding or trimming is allowed')
    differences = []
    for offset in range(0, len(expected), 4):
        left, right = expected[offset:offset + 4], actual[offset:offset + 4]
        if left != right:
            differences.append({'address': f'0x{address + offset:08x}',
                                'expected': left.hex(), 'actual': right.hex()})
    return {'address': f'0x{address:08x}', 'size': len(expected),
            'exact_match': expected == actual,
            'expected_sha256': hashlib.sha256(expected).hexdigest(),
            'actual_sha256': hashlib.sha256(actual).hexdigest(),
            'different_words': len(differences), 'differences': differences}


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('exe', type=Path)
    parser.add_argument('candidate', type=Path)
    parser.add_argument('--address', type=number, required=True)
    parser.add_argument('--size', type=number, required=True,
                        help='Explicit reference byte count. Candidate must have this exact size.')
    parser.add_argument('--format', choices=('elf', 'raw'), default='elf')
    parser.add_argument('--section', default='.text')
    args = parser.parse_args(argv)
    try:
        data = args.candidate.read_bytes()
        actual = elf_section(data, args.section) if args.format == 'elf' else data
        exe_data = args.exe.read_bytes()
        expected = reference(exe_data, args.address, args.size)
        result = compare(expected, actual, args.address)
        result['exe_sha256'] = hashlib.sha256(exe_data).hexdigest()
        result['candidate_file_sha256'] = hashlib.sha256(data).hexdigest()
        result['format'] = args.format
        result['section'] = args.section if args.format == 'elf' else None
        out = ROOT / 'build' / 'compare' / f'{args.address:08x}.json'
        out.parent.mkdir(parents=True, exist_ok=True)
        out.write_text(json.dumps(result, indent=2) + '\n', encoding='utf-8')
    except (OSError, ValueError, struct.error) as exc:
        print(f'error: {exc}', file=sys.stderr)
        return 2
    print('Exact byte match.' if result['exact_match'] else
          f'Byte mismatch: {result["different_words"]} different words.')
    print(f'Local report: {out}')
    return 0 if result['exact_match'] else 1


if __name__ == '__main__':
    sys.exit(main())
