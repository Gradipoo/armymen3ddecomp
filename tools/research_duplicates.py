# SPDX-License-Identifier: GPL-3.0-or-later
"""Find exact duplicate byte-range leads. Reports stay under ignored build/.

Ghidra body size is a count of addresses, not proof of a contiguous range.
This tool tests start-plus-size windows only. It does not decode instructions,
confirm function boundaries, rename symbols, or advance the progress ledger.
"""

from __future__ import annotations

import argparse
import csv
import hashlib
import io
import json
import struct
import sys
import tempfile
from dataclasses import dataclass
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


@dataclass(frozen=True)
class Entry:
    address: int
    size: int
    name: str

    def record(self) -> dict:
        return {'address': f'0x{self.address:08x}', 'size': self.size, 'name': self.name}


def read_inventory(data: bytes) -> list[Entry]:
    reader = csv.DictReader(io.StringIO(data.decode('utf-8-sig')), delimiter='\t')
    if reader.fieldnames != ['address', 'size', 'name']:
        raise ValueError('expected inventory columns: address, size, name')
    entries = []
    seen = set()
    for line, row in enumerate(reader, 2):
        try:
            address = int(row['address'], 16)
            size = int(row['size'], 10)
            name = row['name']
            if None in row or not name or not name.strip():
                raise ValueError('missing name or extra columns')
            if not 0 <= address <= 0xffffffff or address % 4:
                raise ValueError('address must be a 32-bit word-aligned value')
            if size <= 0 or size % 4 or address + size > 0x100000000:
                raise ValueError('size must be positive, word-aligned and not wrap')
            if address in seen:
                raise ValueError('duplicate entry address')
        except (ValueError, TypeError) as exc:
            raise ValueError(f'inventory line {line}: {exc}') from None
        seen.add(address)
        entries.append(Entry(address, size, name))
    if not entries:
        raise ValueError('inventory is empty')
    return sorted(entries, key=lambda e: e.address)


def read_text(data: bytes) -> tuple[int, bytes]:
    if len(data) < 0x800 or data[:8] != b'PS-X EXE':
        raise ValueError('expected a PS-X EXE with a complete header')
    load, size = struct.unpack_from('<II', data, 0x18)
    if load % 4 or size % 4 or load + size > 0x100000000:
        raise ValueError('EXE text range must be word-aligned and not wrap')
    if len(data) < 0x800 + size:
        raise ValueError('EXE text is truncated')
    return load, data[0x800:0x800 + size]


def duplicate_leads(load: int, text: bytes, entries: list[Entry], min_size: int) -> dict:
    if min_size < 8 or min_size % 4:
        raise ValueError('minimum size must be at least eight and word-aligned')
    entries = sorted(entries, key=lambda e: e.address)
    overlapping = set()
    # An interval may contain several later starts. Mark every member involved.
    active: list[Entry] = []
    for entry in entries:
        active = [e for e in active if e.address + e.size > entry.address]
        if active:
            overlapping.add(entry.address)
            overlapping.update(e.address for e in active)
        active.append(entry)
    buckets: dict[bytes, list[Entry]] = {}
    excluded = []
    considered = 0
    for entry in entries:
        reasons = []
        if entry.address in overlapping:
            reasons.append('overlapping inventory windows')
        if entry.address < load or entry.address + entry.size > load + len(text):
            reasons.append('outside EXE text')
        if entry.size < min_size:
            reasons.append('below minimum size')
        if reasons:
            excluded.append({**entry.record(), 'reasons': reasons})
            continue
        offset = entry.address - load
        blob = text[offset:offset + entry.size]
        # Bytes are the key. Hash collisions cannot create a duplicate group.
        buckets.setdefault(blob, []).append(entry)
        considered += 1
    groups = []
    for blob, members in buckets.items():
        if len(members) > 1:
            groups.append({'size': len(blob), 'sha256': hashlib.sha256(blob).hexdigest(),
                           'members': [entry.record() for entry in members]})
    groups.sort(key=lambda group: group['members'][0]['address'])
    return {
        'schema_version': 1,
        'method': 'exact bytes in provisional start-plus-body-size windows',
        'boundary_status': 'unreviewed',
        'warning': 'A body-size count does not prove contiguity. Equal bytes do not prove '
                   'equal behavior at different addresses. Review boundaries, PC-relative '
                   'references, callers and SDK names before reuse.',
        'minimum_size': min_size,
        'inventory_entries': len(entries),
        'considered_entries': considered,
        'excluded': excluded,
        'groups': groups,
    }


def local_output(path: Path) -> Path:
    result = path.resolve()
    build = ROOT.resolve() / 'build'
    if build not in result.parents:
        raise ValueError('report must be inside the repository build directory')
    return result


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('exe', type=Path)
    parser.add_argument('--inventory', type=Path,
                        default=ROOT / 'docs/research/re/game-functions.tsv')
    parser.add_argument('--min-size', type=int, default=16)
    parser.add_argument('--out', type=Path, default=ROOT / 'build/research/duplicates.json')
    args = parser.parse_args(argv)
    try:
        out = local_output(args.out)
        if out in (args.exe.resolve(), args.inventory.resolve()):
            raise ValueError('report must not overwrite an input')
        out.unlink(missing_ok=True)
        exe = args.exe.read_bytes()
        inventory = args.inventory.read_bytes()
        load, text = read_text(exe)
        result = duplicate_leads(load, text, read_inventory(inventory), args.min_size)
        result['exe_sha256'] = hashlib.sha256(exe).hexdigest()
        result['inventory_sha256'] = hashlib.sha256(inventory).hexdigest()
        out.parent.mkdir(parents=True, exist_ok=True)
        temporary = None
        try:
            with tempfile.NamedTemporaryFile(mode='w', encoding='utf-8', dir=out.parent,
                                             prefix='.duplicates-', suffix='.json',
                                             delete=False) as handle:
                temporary = Path(handle.name)
                handle.write(json.dumps(result, indent=2) + '\n')
            temporary.replace(out)
        finally:
            if temporary is not None:
                temporary.unlink(missing_ok=True)
    except (OSError, ValueError, UnicodeError, csv.Error) as exc:
        print(f'error: {exc}', file=sys.stderr)
        return 2
    print(f'{len(result["groups"])} exact duplicate range groups; '
          f'{len(result["excluded"])} entries excluded. Boundaries are unreviewed.')
    print(f'Local report: {out}')
    return 0


if __name__ == '__main__':
    sys.exit(main())
