# SPDX-License-Identifier: GPL-3.0-or-later
"""Report recorded function progress. Never infer completion from a citation.

Reads the Ghidra address/size/name inventory and a separate evidence ledger.
Uses no disc, generated C, or third-party packages. Does not write files.
"""

from __future__ import annotations

import argparse
import csv
import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
INVENTORY = Path('docs/research/re/game-functions.tsv')
LEDGER = Path('docs/function-progress.tsv')
STAGES = ('inventoried', 'identified', 'researched', 'implemented', 'verified')
CATEGORIES = ('unknown', 'game', 'sdk')
FIELDS = ('address', 'category', 'status', 'note', 'source', 'verification')


def address(value: str) -> str:
    try:
        number = int(value, 16)
    except ValueError:
        raise ValueError(f'bad address: {value}') from None
    if not 0 <= number <= 0xFFFFFFFF:
        raise ValueError(f'address out of range: {value}')
    return f'{number:08x}'


def table(path: Path, fields: tuple[str, ...]) -> list[dict[str, str]]:
    with path.open(encoding='utf-8', newline='') as handle:
        reader = csv.DictReader(handle, delimiter='\t')
        if reader.fieldnames != list(fields):
            raise ValueError(f'{path}: expected columns: {", ".join(fields)}')
        rows = []
        seen = set()
        for line, row in enumerate(reader, 2):
            if None in row or any(value is None for value in row.values()):
                raise ValueError(f'{path}:{line}: wrong column count')
            row = {key: value.strip() for key, value in row.items()}
            row['address'] = address(row['address'])
            if row['address'] in seen:
                raise ValueError(f'{path}:{line}: duplicate address {row["address"]}')
            seen.add(row['address'])
            rows.append(row)
        return rows


def evidence(root: Path, value: str) -> None:
    path = Path(value)
    resolved = (root / path).resolve()
    if path.is_absolute() or not resolved.is_relative_to(root.resolve()):
        raise ValueError(f'evidence must be a repository path: {value}')
    rel = resolved.relative_to(root.resolve())
    if any(part in {'build', '.git', 'project', 'Army Men 3D (USA)'} for part in rel.parts):
        raise ValueError(f'evidence must be public: {value}')
    if not resolved.is_file():
        raise ValueError(f'evidence file missing: {value}')


def report(root: Path) -> dict:
    ledger_path = root / LEDGER
    ledger = table(ledger_path, FIELDS) if ledger_path.exists() else []
    for row in ledger:
        if row['category'] not in CATEGORIES or row['status'] not in STAGES:
            raise ValueError(f'{row["address"]}: unknown category or status')
        level = STAGES.index(row['status'])
        for field, required in (('note', 2), ('source', 3), ('verification', 4)):
            if level >= required and not row[field]:
                raise ValueError(f'{row["address"]}: {row["status"]} requires {field}')
            if row[field]:
                evidence(root, row[field])
        if level >= 2:
            note = (root / row['note']).read_text(encoding='utf-8').lower()
            if row['address'] not in note:
                raise ValueError(f'{row["address"]}: research note must cite the address')

    inventory_path = root / INVENTORY
    if not inventory_path.exists():
        if ledger:
            raise ValueError('progress ledger has entries but the function inventory is missing')
        return {'inventory_available': False, 'functions': [], 'counts': None}
    inventory = table(inventory_path, ('address', 'size', 'name'))
    entries = {row['address']: row for row in ledger}
    known = {row['address'] for row in inventory}
    orphaned = entries.keys() - known
    if orphaned:
        raise ValueError(f'ledger addresses absent from inventory: {", ".join(sorted(orphaned))}')
    functions = []
    counts = {stage: {'functions': 0, 'bytes': 0} for stage in STAGES}
    for row in inventory:
        try:
            size = int(row['size'])
        except ValueError:
            raise ValueError(f'{row["address"]}: size must be a positive decimal integer') from None
        if size <= 0:
            raise ValueError(f'{row["address"]}: size must be positive')
        item = dict(row, size=size, category='unknown', status='inventoried',
                    note='', source='', verification='')
        item.update(entries.get(row['address'], {}))
        counts[item['status']]['functions'] += 1
        counts[item['status']]['bytes'] += size
        functions.append(item)
    return {'inventory_available': True,
            'functions': sorted(functions, key=lambda item: item['address']), 'counts': counts}


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--root', type=Path, default=ROOT, help='Repository root')
    parser.add_argument('--json', action='store_true', help='Machine-readable report')
    args = parser.parse_args(argv)
    try:
        result = report(args.root)
    except (OSError, ValueError, csv.Error) as exc:
        print(f'error: {exc}', file=sys.stderr)
        return 1
    if args.json:
        print(json.dumps(result, indent=2))
    elif not result['inventory_available']:
        print('Function inventory unavailable. Progress is unknown, not zero.')
        print('Export docs/research/re/game-functions.tsv with the existing Ghidra import tool.')
    else:
        print(f'Inventoried functions: {len(result["functions"])}')
        print('Recorded status counts are exclusive. Bytes cover inventoried function bodies only.')
        for stage, values in result['counts'].items():
            print(f'{stage}: {values["functions"]} functions, {values["bytes"]} bytes')
        print('category\tstatus\taddress\tsize\tname')
        for row in result['functions']:
            print('\t'.join(str(row[key]) for key in ('category', 'status', 'address', 'size', 'name')))
    return 0


if __name__ == '__main__':
    sys.exit(main())
