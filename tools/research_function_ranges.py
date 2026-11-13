# SPDX-License-Identifier: GPL-3.0-or-later
"""Check local Ghidra body metadata against an EXE and the existing inventory.

Single address ranges are leads for boundary review, not verified functions.
No instructions are decoded. Reports stay inside ignored build/.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import re
import sys
import tempfile
from pathlib import Path

from research_duplicates import local_output, read_inventory, read_text

ROOT = Path(__file__).resolve().parents[1]


def address(value: object) -> int:
    if not isinstance(value, str) or re.fullmatch(r'0x[0-9a-fA-F]{8}', value) is None:
        raise ValueError('metadata addresses must be 0x followed by eight hex digits')
    return int(value, 16)


def validate(metadata: dict, inventory_data: bytes, exe_data: bytes) -> dict:
    if not isinstance(metadata, dict) or type(metadata.get('schema_version')) is not int \
            or metadata['schema_version'] != 1:
        raise ValueError('expected function-range metadata schema 1')
    if metadata.get('language_id') != 'MIPS:LE:32:default':
        raise ValueError('expected MIPS:LE:32:default metadata')
    space = metadata.get('default_address_space')
    if not isinstance(space, str) or not space:
        raise ValueError('missing default address space')
    load, text = read_text(exe_data)
    digest = metadata.get('source_image_sha256')
    if not isinstance(digest, str) or len(digest) != 64:
        raise ValueError('metadata lacks the original imported-image SHA-256')
    if digest.lower() == hashlib.sha256(text).hexdigest():
        source_kind = 'EXE declared text image'
    elif digest.lower() == hashlib.sha256(exe_data).hexdigest():
        source_kind = 'complete EXE'
    else:
        raise ValueError('Ghidra source-image hash does not match this EXE or its declared text')
    inventory = {entry.address: entry for entry in read_inventory(inventory_data)}
    raw = metadata.get('functions')
    if not isinstance(raw, list) or not raw:
        raise ValueError('metadata functions must be a nonempty list')
    functions = {}
    intervals = []
    for row in raw:
        if not isinstance(row, dict):
            raise ValueError('invalid metadata function')
        start = address(row.get('address'))
        size = row.get('size')
        name = row.get('name')
        if start in functions or type(size) is not int or size <= 0 \
                or not isinstance(name, str) or not name:
            raise ValueError('duplicate address or invalid function size/name')
        ranges = row.get('ranges')
        if not isinstance(ranges, list) or not ranges:
            raise ValueError('function needs at least one body range')
        parsed = []
        for item in ranges:
            if not isinstance(item, dict) or not isinstance(item.get('space'), str):
                raise ValueError('invalid body address range')
            first, last = address(item.get('start')), address(item.get('end'))
            if first > last:
                raise ValueError('body range is reversed')
            parsed.append((item['space'], first, last))
        parsed.sort()
        if any(a[0] == b[0] and a[2] >= b[1] for a, b in zip(parsed, parsed[1:])):
            raise ValueError('body ranges overlap within one function')
        if sum(last - first + 1 for _, first, last in parsed) != size:
            raise ValueError('body range lengths disagree with the body address count')
        if not any(s == space and first <= start <= last for s, first, last in parsed):
            raise ValueError('function entry is outside its default-space body')
        reasons = []
        entry = inventory.get(start)
        if entry is None:
            reasons.append('not in inventory')
        elif entry.size != size or entry.name != name:
            reasons.append('inventory size/name differs')
        if len(parsed) != 1:
            reasons.append('body is not one address range')
        if parsed[0][1] != start:
            reasons.append('entry is not the first body address')
        if any(s != space for s, _, _ in parsed):
            reasons.append('body includes another address space')
        if any(first < load or last >= load + len(text) for _, first, last in parsed):
            reasons.append('body outside EXE text')
        if start % 4 or size % 4:
            reasons.append('entry/body size is not word-aligned')
        functions[start] = {'address': f'0x{start:08x}', 'size': size, 'name': name,
                            'range_count': len(parsed), 'reasons': reasons}
        intervals.extend((first, last, start) for s, first, last in parsed if s == space)
    overlapping = set()
    active = []
    for first, last, start in sorted(intervals):
        active = [(end, owner) for end, owner in active if end >= first]
        for _, owner in active:
            if owner != start:
                overlapping.update((owner, start))
        active.append((last, start))
    for start in overlapping:
        functions[start]['reasons'].append('body overlaps another function')
    missing = sorted(set(inventory) - set(functions))
    inconsistent = [row['address'] for row in functions.values()
                    if any(reason in ('not in inventory', 'inventory size/name differs')
                           for reason in row['reasons'])]
    for row in functions.values():
        row['eligible_contiguous_window'] = not row['reasons']
    return {
        'schema_version': 1,
        'method': 'Ghidra address-set metadata checks; no instruction decoding',
        'warning': 'Contiguity reflects the current Ghidra analysis. It does not prove '
                   'code/data classification, return paths, delay slots or function boundaries. '
                   'The source hash identifies the original imported file, not current memory.',
        'source_image_kind': source_kind,
        'ghidra_version': metadata.get('ghidra_version'),
        'inventory_consistent': not missing and not inconsistent,
        'missing_inventory_entries': [f'0x{start:08x}' for start in missing],
        'inconsistent_entries': inconsistent,
        'metadata_functions': len(functions),
        'eligible_contiguous_windows': sum(row['eligible_contiguous_window'] for row in functions.values()),
        'discontiguous_bodies': sum(row['range_count'] > 1 for row in functions.values()),
        'overlapping_bodies': len(overlapping),
        'functions': [functions[start] for start in sorted(functions)],
    }


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('metadata', type=Path)
    parser.add_argument('exe', type=Path)
    parser.add_argument('--inventory', type=Path, default=ROOT / 'docs/research/re/game-functions.tsv')
    parser.add_argument('--out', type=Path, default=ROOT / 'build/research/function-ranges-check.json')
    args = parser.parse_args(argv)
    try:
        out = local_output(args.out)
        if out in {path.resolve() for path in (args.metadata, args.exe, args.inventory)}:
            raise ValueError('report must not overwrite an input')
        out.unlink(missing_ok=True)
        metadata_data = args.metadata.read_bytes()
        exe_data = args.exe.read_bytes()
        inventory_data = args.inventory.read_bytes()
        report = validate(json.loads(metadata_data), inventory_data, exe_data)
        report['metadata_sha256'] = hashlib.sha256(metadata_data).hexdigest()
        report['inventory_sha256'] = hashlib.sha256(inventory_data).hexdigest()
        report['exe_sha256'] = hashlib.sha256(exe_data).hexdigest()
        out.parent.mkdir(parents=True, exist_ok=True)
        temporary = None
        try:
            with tempfile.NamedTemporaryFile(mode='w', encoding='utf-8', dir=out.parent,
                                             prefix='.range-check-', suffix='.json',
                                             delete=False) as handle:
                temporary = Path(handle.name)
                handle.write(json.dumps(report, indent=2) + '\n')
            temporary.replace(out)
        finally:
            if temporary is not None:
                temporary.unlink(missing_ok=True)
    except (OSError, ValueError, UnicodeError) as exc:
        print(f'error: {exc}', file=sys.stderr)
        return 2
    print(f'{report["eligible_contiguous_windows"]} eligible metadata windows; '
          f'{report["discontiguous_bodies"]} discontiguous bodies. Boundaries still need review.')
    print(f'Local report: {out}')
    return 0 if report['inventory_consistent'] else 1


if __name__ == '__main__':
    sys.exit(main())
