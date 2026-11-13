# Function progress

Run `python tools/progress.py`. Use `--json` for a machine-readable report.
This command reads metadata only. It does not read the disc or write files.

The function inventory is `docs/research/re/game-functions.tsv`.
The existing Ghidra import tool exports it with address, size, and name only.
When Ghidra is available, run:

```
python tools/ghidra/import.py build/disc/SLUS_004.91
python tools/progress.py
```

Missing inventory means progress is unknown. Do not estimate a total from
SDK names or research notes. Inventory sizes cover function bodies, not the
whole executable. Discovered function boundaries still need review.

## First inventory

The first export was made on November 13, 2026 with Ghidra 12.2 and the
existing import and export tools. It contains 1,869 candidate functions.
Their body sizes total 488,432 bytes. These are automatic analysis results
from the main executable, using the generic little-endian MIPS processor.
They are not an exhaustive count of game functions. Data, missed boundaries,
and code loaded later need separate review. SDK names were not applied.

The evidence ledger starts empty. All exported functions therefore start as
unknown and inventoried. Existing notes still hold their research facts.
No function was promoted based only on an address citation.

The local import needed an existing Java 25 installation and a writable
Ghidra settings folder. The settings folder and import log stay under
`build/`. The Ghidra project stays under `tools/ghidra/project/`. Only the
address, size, and name export belongs in the public tree.

Record progress in `docs/function-progress.tsv`. Keep one row per function.
Addresses are hexadecimal. Categories are `unknown`, `game`, or `sdk`.
Each row has one current status:

| Status | Meaning | Required evidence |
| --- | --- | --- |
| inventoried | A function boundary was exported. | Inventory row |
| identified | Its purpose or identity was checked. | Review the name and category |
| researched | A research note describes the supported behavior. | Note path with the address |
| implemented | Our code implements the researched behavior. | Note and source paths |
| verified | The implementation passed a stated behavior or matching check. | Note, source, and verification record paths |

The ledger columns are `address`, `category`, `status`, `note`, `source`,
and `verification`. Evidence paths are relative to the repository root.
Leave unused fields empty. Evidence must stay in public repository files.
The verification record states the check, result, scope, and remaining gaps.
It may link to a test. A test file alone does not record a passing result.

The tool checks the ledger's structure and evidence paths. People still check
the claims. File existence does not prove correct behavior. A partial block
note does not establish that a whole function is researched. Follow AGENTS.md
for note boundaries. Keep existing block notes.

Functions without a ledger row remain unknown and inventoried. SDK signature
hits do not advance status automatically. Preserve unresolved names as leads.
The existing gap tool still lists citation gaps. This report tracks a separate
question: how far each function has progressed toward checked code.

Keep the ledger outside `docs/research/`. Otherwise its address rows would
count as research citations in the gap tool. Do not add placeholder notes
just to raise a count. Keep raw code, assembly, and local traces under `build/`.

Update one function at a time with its code and evidence. Run:

```
python tools/progress.py
python -m unittest discover -s tests
python tools/pr_guard.py
```
