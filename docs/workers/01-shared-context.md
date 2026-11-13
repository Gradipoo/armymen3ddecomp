# R01: Shared type context

Status: Passed synthetic trial. Reviewed November 13, 2026.
See the [result](results/shared-context.md). Retail adoption is not proved.

## Question and scope

Does a small confirmed context remove repeated type repair in local m2c
drafts? Evaluate the [m2c context interface](https://github.com/matt-kempster/m2c#usage)
and the local part of [SOTN's preparation workflow](https://github.com/Xeeynamo/sotn-decomp/blob/master/tools/m2ctx.py).
Do not copy another game's types or use its upload workflow.

Permitted public file: `docs/workers/results/shared-context.md`.
Permitted local directory: `build/research/context/`.
Do not edit `tools/prepare_function.py` or `docs/ANALYSIS.md`.
Read `docs/WORKERS.md` for the common evidence and stop rules.

## Inputs and commands

Use the installed m2c revision recorded in `docs/analysis-tools.json`.
Create a tiny original assembly fixture locally. Its function loads signed
halfwords at offsets 0 and 2 through a0, adds them, returns through ra,
and uses a nop delay slot. Declare a two-field signed-short struct and
the function prototype in a separate local preprocessed context file.
This is synthetic input, with no game or SDK code.

```
build/analysis/venv/bin/m2c --help
build/analysis/venv/bin/m2c --target mipsel-gcc-c --no-cache build/research/context/fixture.s
build/analysis/venv/bin/m2c --target mipsel-gcc-c --no-cache --context build/research/context/context.h build/research/context/fixture.s
python3 -m unittest discover -s tests -p test_prepare_function.py
python3 tools/pr_guard.py
```

Capture stdout to separate local files. Preserve the argument lists,
logs and output hashes. Confirm exact options from this pinned `--help`.

## Acceptance and evidence

Both runs must exit zero. Compare unknown-field declarations, inferred
prototypes, field offsets, field widths, signedness, and casts. The typed
draft must use both declared fields at their correct offsets. Merely
changing names does not count as improved recovery. Count manual edits
needed to reach a correctly typed expression in each draft, using a
written rule. Record elapsed time for five identical warm runs of each
mode. Timing is secondary to correctness and may be inconclusive.

Run a negative control with the wrong field width. Record whether m2c
reports a conflict or emits a misleading draft. A supplied prototype is
an assumption, not corroborating evidence. Record this limit explicitly.

Propose a minimal shared-context format with type, offset, signedness,
evidence address, confidence and source revision. Keep the proposal in
the result report. Do not add retail types to public headers in this task.

## Known failure modes

Host headers use different pointer and long sizes. m2c has only limited
preprocessing. Generated declarations can look plausible with wrong
context. A successful parse does not prove a field layout. Raw C and
`.m2c` context caches must remain under the local task directory.
