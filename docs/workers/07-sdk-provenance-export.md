# R07: Preserve SDK scan provenance

Status: Pending. No worker has executed this assignment.

## Question and scope

Can the source-label evidence proved useful in R03 be retained by a small
standard-library companion to the existing scanner? Read the reviewed
[R03 report](results/sdk-provenance.md) and its local audit. Keep the named
call rule, accepted names and existing scanner output unchanged.

Permitted public files: `tools/research_sdk_provenance.py`,
`tests/test_research_sdk_provenance.py`, and
`docs/workers/results/sdk-provenance-export.md`.
Permitted local directory: `build/research/sdk-export/`.
Do not edit `sdk_scan.py`, `sdk_match.py`, SDK tables or game notes.
Read `docs/WORKERS.md`.

## Inputs and method

Use only original synthetic signatures in public tests. The retail phase
may use the existing local signature checkout. Do not import its files or
assume that its absent license declaration permits redistribution.

Reuse the existing scanner's parser, alignment and masked predicate. A
fixed-byte anchor and per-pattern cache can locate candidates, but every
candidate must pass the unchanged predicate. Preserve deterministic source
file, record and label order. Handle masks with separated fixed bytes,
multiple matches, aliases, internal labels, duplicate records, labels out
of bounds and records below the minimum fixed-byte count.

Write only local JSON under the real repository `build/` directory.
Record input/source revision and hashes, file and record index, source
record digest, mask digest, fixed and total bytes, signature start, label
offset, source version, location count, competing names and decision reason.
Keep raw masks and executable bytes out of the report. Do not use a
confidence percentage. Do not write a candidate accepted-name table in
this first implementation. No existing name changes automatically.

## Commands and acceptance

```
python3 -m unittest discover -s tests -p 'test_sdk_*.py' -v
python3 -m unittest discover -s tests -p test_research_sdk_provenance.py -v
python3 tools/research_sdk_provenance.py --help
python3 tools/pr_guard.py
```

Document the new CLI's exact local commands after implementing it. Test
report path escapes, input collisions and failed-run invalidation. Use
synthetic cases to require byte-for-byte equality with the existing
scanner's projected address/name/version output. Include a differential
oracle over generated short synthetic images and masks, with a fixed seed.

For the local retail check, pin the same fourteen source directories and
input hashes used in R03. Projected rows must agree with the reviewed
production outputs for every version. Rebuild the union only in the
local report: 383 accepted rows, 203 ambiguous addresses, 39 accepted rows
with all-version coverage. A difference must remain a reported failure,
not be resolved by changing filters or the accepted table.

For a controlled speed check, use the same single source-version directory,
input and output scope for both tools. Run each five times after one warm
run. Record parsing and scanning scope, memory limits and total output
cost. Report no speed gain unless equivalent output and measured times
support it. This task does not identify SDK versions or verify names.

## Known failure modes

Caching by name or mask digest alone can lose record identity. An anchor
with the wrong offset can miss aligned matches. Repeated masks must retain
all labels and source records. Version repetitions are correlated. Do not
use this tool to enter SDK bodies or expand the accepted name table.
