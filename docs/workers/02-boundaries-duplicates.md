# R02: Boundaries and duplicate leads

Status: Passed filter and metadata trial. Reviewed November 13, 2026.
See the [result](results/boundaries-duplicates.md). Whole routines and
shared behavior remain unresolved.

## Question and scope

Can exact duplicate leads avoid researching the same routine twice,
without treating inferred body sizes as trusted ranges? Start with our
small range filter. Compare the design with [SOTN's duplicate tool](https://github.com/Xeeynamo/sotn-decomp/tree/master/tools/dups).
Use spimdisasm or Ghidra for boundary review rather than writing another
MIPS decoder. Do not rename symbols or merge implementations.

Permitted public file: `docs/workers/results/boundaries-duplicates.md`.
Permitted local directory: `build/research/duplicates/`.
The existing inventory is read-only. Read `docs/WORKERS.md`.

## Inputs and commands

```
python3 -m unittest discover -s tests -p test_research_duplicates.py -v
python3 tools/research_duplicates.py --help
python3 tools/research_duplicates.py LOCAL_EXE --out build/research/duplicates/leads.json
python3 tools/sdk_match.py LOCAL_EXE
python3 tools/pr_guard.py
```

Replace `LOCAL_EXE` with the owner's local path. The scanner writes a
local JSON report. Its input SHA-256 values must agree with the local
manifest. No generated code is part of the public result.

## Acceptance and evidence

Pass the synthetic tests. Independently check that overlapping windows,
truncated EXEs, unaligned entries, small entries and output paths outside
`build/` cannot silently create accepted groups. Add no production changes
in this task. Report any defect to the coordinator with a synthetic case.

For the retail phase, report total entries, excluded entries, groups and
grouped entries. Review at most five groups, ordered by address. Check
Ghidra's body address ranges, branch targets and delay slots. A body-size
count does not show contiguity. Record whether each proposed range is one
whole routine, a partial routine, data, or unresolved. Equal instructions
at different PCs can reference different targets or globals. Check that
before suggesting shared behavior.

Check SDK names before inspection. A named SDK body is skipped, with its
name and source recorded locally. Do not enter it for this evaluation.
Do not decode a new unnamed game body under this tools task. If a lead
needs that work, hand its address to the coordinator for a one-gap task.
Counts and the limits of the filter are sufficient here.

## Known failure modes

Short return stubs inflate duplicate counts. Separate data can look like
code. Exact equality misses equivalent routines with different addresses,
constants or register use. This is intentional. Do not mask bytes or
promote a similarity score to an equality or behavior claim.
