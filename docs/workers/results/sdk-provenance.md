# R03 result: SDK name provenance

Date: November 13, 2026. Outcome: Passed for the synthetic controls and
local provenance audit. The ambiguous-address count differs from the
existing note. Reviewed by the research coordinator on the same date.
Host: macOS 27.2.1 ARM64, Python 3.15.2.

No names, tables, tools, inventory, notes or ledger status were changed.
No function body was disassembled. No code or signatures were imported.

## Source and license

The existing clean local signature checkout is
[`e9e46e7e133ef275a79bfce650924f98edb086bc`](https://github.com/lab313ru/psx_psyq_signatures/tree/e9e46e7e133ef275a79bfce650924f98edb086bc).
It contains sixteen version directories. The audit selected the fourteen
versions listed in the existing SDK note. It did not select directories
3610 and 3611. No reason for their earlier omission was established.
The local manifest records the selected file hashes and directory layout.

No license, copying or notice file was found in the checkout outside its
Git metadata. Its [root README](https://github.com/lab313ru/psx_psyq_signatures/blob/e9e46e7e133ef275a79bfce650924f98edb086bc/README.md)
has no license declaration. GitHub's repository metadata returned a null
license field. This is not permission to import the files. Raw signatures
remain local. No SDK archive was fetched.

The separate [psy-q-decomp README](https://github.com/sozud/psy-q-decomp/blob/bda8aa2a39b2b91f4aa87173a2966b9ed285d534/README.md)
declares a current target of Psy-Q 3.5. Its
[MIT license](https://github.com/sozud/psy-q-decomp/blob/bda8aa2a39b2b91f4aa87173a2966b9ed285d534/LICENSE)
does not license the signature repository or SDK archives. This audit
neither identifies Army Men's SDK version nor its game compiler.
Our scanner code uses GPL-3.0-or-later.

## Synthetic controls

An original synthetic EXE has two copies of an exact pattern and one
masked pattern. Two synthetic version directories repeat the records.
Aliases share an entry address. Internal labels point four bytes into
each pattern. A second record repeats the exact name and pattern. A weak
record has fewer than the scanner's eight required fixed bytes.

| Record in each synthetic version | Fixed bytes | Total bytes | Wildcard density | Locations |
| --- | --- | --- | --- | --- |
| Exact pattern with alias and internal label | 8 | 8 | 0% | 2 |
| Masked pattern with internal label | 10 | 12 | 16.67% | 1 |
| Repeated exact name and pattern | 8 | 8 | 0% | 2 |
| Below-threshold control | 7 | 8 | 12.5% | Not scanned |

The unchanged scanner exited zero. Eight source records produced six
eligible records and two distinct eligible patterns. Output had twenty
rows, sixteen distinct rows, six internal-label rows and two addresses
with competing names. The exact name appeared at two addresses. Version
repetition and duplicate records increased row counts without adding
independent evidence. Wildcard density is descriptive, not a confidence
percentage.

The current output retains address, name and version. It loses the source
revision, file, record index, source digest, pattern length, fixed-byte
count, signature start, label offset and location count. It does not flag
internal labels, aliases, repeated records or conflicting names. Two
identical output lines can have different source records.

`sdk_match.py` also prints table names and pattern hits in the same form.
The table path checks whether an address is in the loaded image. It does
not revalidate the table's name against bytes. An unchanged table is thus
an input assertion, not a fresh signature match or external confirmation.

## Retail count reproduction

The local audit searched for a fixed run, then verified each candidate
with the unchanged scanner's masked predicate and alignment rules. It
retained every selected source record and label. Its complete synthetic
output matched the unchanged scanner. A fresh production scan of version
260 also matched exactly. All fourteen fresh version outputs matched the
earlier saved outputs byte for byte. The full provenance audit was not a
run of the unchanged scanner over all versions.

For regeneration, drop names starting with `loc_` or `text_`. Group the
remaining hits by address across the selected versions. Accept an address
only when that union contains one name. Retain all other addresses as
ambiguous. This rule reproduces the current table exactly.

| Count | Observed | Difference from the existing claim or table |
| --- | --- | --- |
| Selected signature records | 18,120 | No earlier count supplied |
| Raw hit rows | 15,484 | Zero differences from saved outputs |
| Source records with hits | 1,994 | No earlier count supplied |
| Distinct patterns with hits | 232 | No earlier count supplied |
| Accepted table rows | 383 | 0 |
| Distinct names in those rows | 375 | No earlier count supplied |
| Ambiguous addresses | 203 | -3 against the note's 206 |
| Current table rows missing from regeneration | 0 | 0 |
| Regenerated rows absent from the table | 0 | 0 |
| `sdk_match.py` output rows | 386 | 383 table rows plus 3 pattern hits |

No cause was established for the ambiguous-count difference. The audit
does not change the historical note or any table entry.

Accepted names have source hits in between one and fourteen versions.
Only 39 accepted rows have hits in all fourteen. Eighteen have hits in
one version. The regeneration rule means no competing non-internal name
was observed in the selected union. It does not mean every version
matched every accepted address. Repeated SDK versions are not independent
statistical observations. No external name confirmations were performed.

## Proposed local provenance record

| Field | Required purpose |
| --- | --- |
| Input EXE digest | Bind the result to a local input without publishing bytes |
| Source revision, file and file digest | Identify the source checkout and file |
| Record index and record digest | Distinguish repeated records in the same file |
| Signature digest, fixed and total bytes | Distinguish masks and describe their scope |
| Signature start and label offset | Separate a routine entry from an internal label |
| Label name and index | Preserve aliases and repeated labels |
| Source version and aggregated version set | Preserve source labels without a confidence score |
| Match count and competing names | Expose non-unique locations and conflicting interpretations |
| Evidence kind | Table name, pattern hit, ambiguous lead, or external confirmation |
| Decision and reason | Explain acceptance, exclusion, conflict or unresolved status |

A digest of a mask alone is not a source-record identity. The same mask
can occur with different labels, offsets, files and versions. A later
regeneration command should pin the input hashes, selected version list,
filter rule and tool revision. It should write the candidate table and
ambiguity report under `build/`, compare candidate and current table as
sets and ordered rows, and require review before changing names. It must
not promote a signature lead to an externally confirmed name.

## Evidence and checks

Local artifacts are in `build/research/sdk/`: `audit.py`, `finalize.py`,
`manifest.json`, `synthetic-provenance.json`, `synthetic-summary.json`,
`retail-provenance.json`, `retail-summary.json`, `name-evidence.json`,
`name-decisions.json`, `saved-scan-checks.json`, and captured command logs.
The manifest records exact argument lists, revisions, hashes, exit codes,
elapsed times and artifact locations. The name-evidence map traces all
383 accepted rows to 2,461 source-label hit records. These are signature
observations, not independent confirmations.

The fixed-anchor audit over fourteen versions took 9.06 seconds. The
unchanged scanner over version 260 took 10.90 seconds. The scopes differ,
so these figures are not a controlled performance comparison. No adopted
scanner improvement or review-time saving was measured.

```
python3 -m unittest discover -s tests -p 'test_sdk_*.py' -v
python3 build/research/sdk/audit.py
python3 build/research/sdk/run_scanner260.py
python3 build/research/sdk/finalize.py
python3 tools/pr_guard.py
```

Fifteen SDK tests passed. The synthetic controls, production version-260
cross-check and saved-output checks passed. The guard passed. There were
zero failed attempts. Preserve the current named-call rule. Add provenance
in a separate focused tooling change before expanding the accepted names.

The coordinator checked source, tool and artifact hashes, ran the unchanged
production scanner independently for all fourteen versions, and reproduced
every worker output. The coordinator then independently rebuilt the name
union, ordered table and coverage histogram. All 383 rows matched, with
203 ambiguous addresses, 39 accepted rows covered by every version, and
18 covered by one version. The local `review/` folder retains these runs.
The dated SDK summary correction was made after this review. No table or
matching behavior changed.
