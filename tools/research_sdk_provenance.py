# SPDX-License-Identifier: GPL-3.0-or-later
"""Keep SDK signature evidence in local JSON. Never changes accepted names.

Reuses sdk_scan's parsers, masked predicate, minimum fixed bytes and alignment.
The cache stores locations by full parsed mask, not by label or digest. Source
records and labels remain distinct. Masks and executable bytes are not exported.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import sys
import tempfile
from collections import defaultdict
from pathlib import Path

import sdk_scan as SCAN

ROOT = Path(__file__).resolve().parents[1]


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def canonical_digest(value: object) -> str:
    return sha(json.dumps(value, sort_keys=True, separators=(',', ':')).encode('utf-8'))


def source_paths(directory: Path, versions: list[str] | None) -> list[Path]:
    if versions:
        if len(set(versions)) != len(versions) or any(
                not value or value in ('.', '..') or Path(value).name != value or '/' in value
                or '\\' in value for value in versions):
            raise ValueError('versions must be distinct immediate directory names')
        directories = [directory / value for value in versions]
    else:
        directories = [directory]
    paths = []
    for selected in directories:
        if not selected.is_dir():
            raise SCAN.ToolError(f'bad directory: {selected}')
        paths.extend(path for path in sorted(selected.rglob('*.json')) if path.is_file())
    return paths


def load_records(directory: Path, paths: list[Path]) -> tuple[list[dict], list[dict], list[dict]]:
    records, files, skipped = [], [], []
    for file_index, path in enumerate(paths):
        try:
            data = path.read_bytes()
            raw = json.loads(data.decode('utf-8'))
        except (OSError, UnicodeDecodeError, json.JSONDecodeError):
            raise SCAN.ToolError(f'unreadable json: {path}') from None
        if not isinstance(raw, list):
            raise SCAN.ToolError(f'unreadable json: {path}')
        relative = path.relative_to(directory).as_posix()
        file_digest = sha(data)
        files.append({'file_index': file_index, 'path': relative, 'sha256': file_digest,
                      'version': path.parent.name, 'source_records': len(raw)})
        for index, item in enumerate(raw):
            if not isinstance(item, dict):
                raise SCAN.ToolError(f'unreadable json: {path}')
            identity = {'file_index': file_index, 'file': relative,
                        'file_sha256': file_digest, 'record_index': index,
                        'source_record_sha256': canonical_digest(item)}
            if 'sig' not in item or 'labels' not in item:
                skipped.append({**identity, 'reason': 'record lacks sig or labels; production skips it'})
                continue
            # These are the production parsers, including their validation rules.
            pattern, fixed = SCAN._parse_sig(item['sig'], path)
            labels = SCAN._parse_labels(item['labels'], path)
            normalized = ' '.join('??' if byte is None else f'{byte:02x}' for byte in pattern)
            records.append({**identity, 'record_id': f'{file_index}:{index}',
                            'version': path.parent.name, 'pattern': pattern,
                            'mask_sha256': sha(normalized.encode('ascii')),
                            'fixed_bytes': fixed, 'total_bytes': len(pattern),
                            'eligible': fixed >= SCAN.MIN_FIXED,
                            'labels': [{'label_index': label_index, 'name': name,
                                        'offset': offset, 'in_signature': 0 <= offset < len(pattern)}
                                       for label_index, (name, offset) in enumerate(labels)]})
    return records, files, skipped


def fixed_anchor(pattern: SCAN.Pattern) -> tuple[int, bytes]:
    longest, best_offset = b'', 0
    current = bytearray()
    start = 0
    for index, byte in enumerate(pattern):
        if byte is None:
            current.clear()
        else:
            if not current:
                start = index
            current.append(byte)
            if len(current) > len(longest):
                longest, best_offset = bytes(current), start
    if not longest:
        raise ValueError('a scanned pattern must have a fixed byte')
    return best_offset, longest


def find_locations(text: bytes, pattern: SCAN.Pattern, stats: dict) -> tuple[int, ...]:
    offset, anchor = fixed_anchor(pattern)
    found = []
    search = 0
    while True:
        hit = text.find(anchor, search)
        if hit < 0:
            return tuple(found)
        search = hit + 1
        stats['anchor_occurrences'] += 1
        candidate = hit - offset
        if candidate < 0 or candidate % SCAN.STEP or candidate + len(pattern) > len(text):
            continue
        stats['predicate_calls'] += 1
        if SCAN._match(text, candidate, pattern):
            found.append(candidate)


def scan_records(load: int, text: bytes, records: list[dict]) -> tuple[list[dict], dict]:
    cache: dict[SCAN.Pattern, tuple[int, ...]] = {}
    stats = {'distinct_patterns_scanned': 0, 'cache_reuses': 0,
             'anchor_occurrences': 0, 'predicate_calls': 0}
    hits = []
    for ordinal, record in enumerate(records):
        if not record['eligible']:
            record['location_count'] = None
            record['signature_starts'] = []
            continue
        pattern = record['pattern']
        if pattern not in cache:
            cache[pattern] = find_locations(text, pattern, stats)
        else:
            stats['cache_reuses'] += 1
        locations = cache[pattern]
        record['location_count'] = len(locations)
        record['signature_starts'] = [f'0x{(load + index) & 0xffffffff:08x}' for index in locations]
        for index in locations:
            base = (load + index) & 0xffffffff
            for label in record['labels']:
                if label['in_signature']:
                    hits.append({'text_offset': index, 'record_ordinal': ordinal,
                                 'record_id': record['record_id'],
                                 'signature_start': f'0x{base:08x}',
                                 'address': f'0x{(base + label["offset"]) & 0xffffffff:08x}',
                                 'name': label['name'], 'version': record['version'],
                                 'label_index': label['label_index'], 'label_offset': label['offset'],
                                 'location_count': len(locations)})
    hits.sort(key=lambda row: (row['text_offset'], row['record_ordinal'], row['label_index']))
    stats['distinct_patterns_scanned'] = len(cache)
    return hits, stats


def projection(hits: list[dict]) -> bytes:
    """The exact byte stream printed by sdk_scan, including duplicate rows."""
    return ''.join(f'{row["address"]} {row["name"]} {row["version"]}\n'
                   for row in hits).encode('utf-8')


def make_report(records: list[dict], files: list[dict], skipped: list[dict],
                hits: list[dict], stats: dict) -> dict:
    names: dict[str, set[str]] = defaultdict(set)
    versions: dict[tuple[str, str], set[str]] = defaultdict(set)
    for row in hits:
        if not row['name'].startswith(('loc_', 'text_')):
            names[row['address']].add(row['name'])
            versions[(row['address'], row['name'])].add(row['version'])
    source_versions = list(dict.fromkeys(row['version'] for row in files))
    decisions = []
    for address, alternatives in sorted(names.items()):
        competing = sorted(alternatives)
        decisions.append({'address': address, 'names': competing,
                          'decision': 'unique_name_lead' if len(competing) == 1 else 'ambiguous_name_lead',
                          'reason': 'one non-internal name in selected union' if len(competing) == 1
                          else 'multiple non-internal names in selected union',
                          'versions_by_name': {name: sorted(versions[(address, name)]) for name in competing}})
    enriched = []
    for row in hits:
        internal = row['name'].startswith(('loc_', 'text_'))
        competing = sorted(names[row['address']])
        reason = ('loc_/text_ label excluded from non-internal union' if internal else
                  'multiple non-internal names at this address' if len(competing) > 1 else
                  'one non-internal name observed; signature lead only')
        enriched.append({**row, 'evidence_kind': 'signature_hit',
                         'label_position': 'signature_start' if row['label_offset'] == 0 else 'inside_signature',
                         'competing_names': competing,
                         'decision': 'internal_label_lead' if internal else
                         'ambiguous_name_lead' if len(competing) > 1 else 'unique_name_lead',
                         'reason': reason})
    clean = []
    for row in records:
        clean.append({key: value for key, value in row.items() if key != 'pattern'} | {
            'scan_decision': 'scanned' if row['eligible'] else 'below_minimum_fixed_bytes',
            'reason': 'production fixed-byte threshold met' if row['eligible'] else
            'fewer fixed bytes than the production minimum'})
    unique = [row for row in decisions if row['decision'] == 'unique_name_lead']
    all_versions = sum(len(row['versions_by_name'][row['names'][0]]) == len(source_versions)
                       for row in unique)
    return {'schema_version': 1, 'method': 'fixed-byte anchor, full-mask cache, unchanged sdk_scan predicate',
            'warning': 'Signature observations only. Source versions are correlated labels. '
                       'No SDK version, external name confirmation or accepted-name update is established.',
            'scanner_rules': {'step': SCAN.STEP, 'minimum_fixed_bytes': SCAN.MIN_FIXED},
            'source_versions': source_versions, 'files': files, 'records': clean,
            'skipped_non_signature_records': skipped, 'hits': enriched,
            'address_decisions': decisions, 'scan_statistics': stats,
            'summary': {'signature_records': len(records),
                        'eligible_records': sum(row['eligible'] for row in records),
                        'source_records_with_hits': sum(bool(row['location_count']) for row in records),
                        'raw_hit_rows': len(hits), 'unique_name_lead_addresses': len(unique),
                        'ambiguous_name_addresses': len(decisions) - len(unique),
                        'unique_name_leads_with_all_source_versions': all_versions},
            'projected_output_sha256': sha(projection(hits)),
            'projected_output_bytes': len(projection(hits))}


def output_path(path: Path, exe: Path, directory: Path, inputs: list[Path]) -> Path:
    out = path.resolve()
    if ROOT.resolve() / 'build' not in out.parents or out.suffix != '.json':
        raise ValueError('report must be a .json file inside the real repository build directory')
    source = directory.resolve()
    if out == source or source in out.parents:
        raise ValueError('report must not be inside the signature source directory')
    for item in [exe, *inputs]:
        if out == item.resolve() or (out.exists() and item.exists() and out.samefile(item)):
            raise ValueError('report must not overwrite an input or its alias')
    return out


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('exe', type=Path)
    parser.add_argument('signatures', type=Path)
    parser.add_argument('--source-revision', required=True,
                        help='Explicit source identity asserted by the caller; file hashes bind actual inputs.')
    parser.add_argument('--version', action='append', help='Select an immediate version directory; repeat in source order.')
    parser.add_argument('--out', type=Path, default=ROOT / 'build/research/sdk-export/provenance.json')
    args = parser.parse_args(argv)
    try:
        if not args.source_revision.strip():
            raise ValueError('source revision must not be empty')
        # Validate the output and invalidate any previous report before parsing input.
        out = output_path(args.out, args.exe, args.signatures, [])
        try:
            paths = source_paths(args.signatures, args.version)
        except (OSError, ValueError, SCAN.ToolError):
            out.unlink(missing_ok=True)
            raise
        output_path(out, args.exe, args.signatures, paths)
        out.unlink(missing_ok=True)
        load, text = SCAN.read_exe(args.exe)
        exe_data = args.exe.read_bytes()
        # Bind the second read to the exact image used by the production reader.
        if (int.from_bytes(exe_data[0x18:0x1c], 'little') != load or
                int.from_bytes(exe_data[0x1c:0x20], 'little') != len(text) or
                exe_data[SCAN.TEXT_OFF:SCAN.TEXT_OFF + len(text)] != text):
            raise ValueError('EXE changed while reading inputs')
        records, files, skipped = load_records(args.signatures, paths)
        hits, stats = scan_records(load, text, records)
        report = make_report(records, files, skipped, hits, stats)
        report['source_revision'] = args.source_revision
        report['source_revision_assurance'] = 'caller assertion; file hashes identify the parsed inputs'
        report['selected_directories'] = args.version
        report['exe_sha256'] = sha(exe_data)
        report['tool_sha256'] = sha(Path(__file__).read_bytes())
        report['production_scanner_sha256'] = sha(Path(SCAN.__file__).read_bytes())
        out.parent.mkdir(parents=True, exist_ok=True)
        temporary = None
        try:
            with tempfile.NamedTemporaryFile(mode='w', encoding='utf-8', dir=out.parent,
                                             prefix='.sdk-provenance-', suffix='.json',
                                             delete=False) as handle:
                temporary = Path(handle.name)
                json.dump(report, handle, indent=2)
                handle.write('\n')
            temporary.replace(out)
        finally:
            if temporary is not None:
                temporary.unlink(missing_ok=True)
    except (OSError, ValueError, SCAN.ToolError) as exc:
        print(f'error: {exc}', file=sys.stderr)
        return 2
    print(f'{len(hits)} signature hit rows. No accepted names changed.')
    print(f'Local report: {out}')
    return 0


if __name__ == '__main__':
    sys.exit(main())
