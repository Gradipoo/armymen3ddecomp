# R04 result: Synthetic object viewer checks

Date: November 13, 2026. Outcome: Passed for objdiff's synthetic object
checks. The asm-differ path is blocked by objdump argument compatibility.
Cause-location timing remains unmeasured. Reviewed by the research
coordinator on the same date. No speed improvement or retail result was established.
No retail input was read.

## What was prepared

The pinned
[asm-differ source](https://github.com/simonlindholm/asm-differ/tree/0dd09af8f8008f1f880327cf0aca3b26d2562ea2)
and dependency wheels were downloaded into `build/research/diff/`.
The viewer installed into that directory's isolated Python 3.12 environment.
No system package or shared analysis environment was changed. No upstream
code was copied into public source files.

Its [license is the Unlicense](https://github.com/simonlindholm/asm-differ/blob/0dd09af8f8008f1f880327cf0aca3b26d2562ea2/LICENSE).
The source metadata and downloaded wheel notices were checked before
the viewer's first invocation. Exact archive and wheel hashes and retained
license files are local. The installed dependency selections were:

| Package | Version | Reviewed declaration |
| --- | --- | --- |
| colorama | 0.4.6 | BSD-3-Clause |
| cxxfilt | 0.3.0 | BSD-2-Clause |
| Levenshtein | 0.27.1 | GPL-2.0-or-later |
| RapidFuzz | 3.14.6 | MIT |
| watchdog | 6.0.0 | Apache-2.0 |
| poetry-core, for the local package build | 2.2.1 | MIT, with retained dependency notices |

The host is macOS 27.2.1 ARM64. LLVM 23.1.5 reports MIPS and MIPS little
endian targets. No GNU MIPS objdump was found on PATH. The task's fixed
assembler settings were used only for original synthetic inputs.

## Setup failures and their accounting

1. The first source download could not resolve the public source host in
   restricted execution. The same authorized download later succeeded
   with network access. The pinned source and dependency installation
   then completed.
2. The first `asm-differ --help` invocation exited 1. This revision loads
   `diff_settings.py` before displaying help. The required local settings
   file had not been created.
3. The next setup command used repository-relative paths while its working
   directory was already the local trial directory. The shell could not
   find the source path or viewer path. It exited 127 before creating
   settings or invoking the viewer.

The last two failures were setup mistakes in this trial. They do not show
a defect in asm-differ. An initial assessment incorrectly combined these
unrelated failures into one stop count. That assessment is retained
locally. The count was corrected by problem before continuing with an
absolute-path settings file. Corrected `--help` then exited zero.

One report-finalization command also had a here-document delimiter error.
It did not invoke the viewer. This reporting error is separate from
viewer compatibility. The local attempt ledger keeps these distinctions.
No setup problem was retried to three failures.

## asm-differ diagnostics

The pinned [settings example](https://github.com/simonlindholm/asm-differ/blob/0dd09af8f8008f1f880327cf0aca3b26d2562ea2/diff_settings.py)
allows explicit input paths, architecture and objdump. The pinned
[viewer source](https://github.com/simonlindholm/asm-differ/blob/0dd09af8f8008f1f880327cf0aca3b26d2562ea2/diff.py)
defines `mipsel` with little endian and `mips:3000`. Its raw binary path
constructs GNU-style `-bbinary` and endian arguments. It has separate
LLVM handling in the ELF path.

The corrected settings selected `mipsel` and the existing explicit LLVM
objdump path. Both inputs were original twelve-byte synthetic fixtures.
The viewer ran from the settings directory with `--no-pager --format
plain`, start zero and full end address twelve. Immediate and address
ignoring were left disabled. Watch mode and automatic builds were off.

| Mode | Actual result |
| --- | --- |
| Raw, identical fixture | Exit 1. LLVM rejected `-b` from the constructed `-bbinary` argument. |
| ELF, identical fixture | Exit 1. The unconditional `-m mips:3000` arguments made LLVM treat `mips:3000` as a missing file. |

The ELF run used `--elf fixture`. Neither mode reached a diff. The raw
and ELF errors are two failed attempts at the same objdump argument
compatibility problem. No further mode, flag variation, wrapper or system
tool installation was attempted. The three-failure threshold was not
reached for that problem. Continuing needs a compatible tool or a
separately reviewed upstream compatibility change.

Register normalization, immediate handling, relocation display, insertion
alignment and full-range diff output were not verified in asm-differ.
`pip freeze` was not run; installed selections are recorded by the
successful offline install log.

## Objdiff alternative

Objdiff was not already installed. The official
[v3.8.3 release](https://github.com/encounter/objdiff/releases/tag/v3.8.3)
provides a native macOS ARM64 CLI. Its SHA-256 digest was verified against
the official release metadata before execution. The source offers
[MIT](https://github.com/encounter/objdiff/blob/v3.8.3/LICENSE-MIT) or
[Apache-2.0](https://github.com/encounter/objdiff/blob/v3.8.3/LICENSE-APACHE)
terms. Both notices and the release metadata are retained locally.
No system install, source import or objdump wrapper was needed.

The native CLI reported 3.8.3. Its help was checked. One-shot object
comparison used `--target`, `--base`, `--output`, `--format json-pretty`,
and the complete `fixture` function symbol. Defaults were retained.
The target objects were assembled from our original synthetic sources.
Their symbol sizes are known. No retail object or relocation was invented.

| Case | Actual objdiff result | Score |
| --- | --- | --- |
| Identical | Three matching instruction rows | 100% |
| Changed register | First argument marked different, `v0` versus `v1` | 98.33% |
| Changed constant | Third argument marked different, 7 versus 8 | 99.67% |
| Inserted instruction | Extra nop marked `DIFF_INSERT`; later instructions align | 66.67% |
| Unresolved call | Argument mismatch with `external_target` and `R_MIPS_26` metadata | 98.75% |
| Same unresolved object on both sides | Matching object view, with relocation still present | 100% |

All six native CLI commands exited zero. Register and immediate changes
were exposed. The insertion view covered twelve versus sixteen bytes and
retained the extra instruction. Call relocation metadata was visible.
These are structured JSON instruction views. The GUI was not tested.

The extra unresolved-object control is important. Its object self-score
is 100%. A synthetic reference with the same raw instruction bytes still
gets exit 2 from our exact comparator because the candidate ELF contains
an unresolved relocation. A viewer score cannot bypass that check.

## Unaffected exact-comparator checks

The separate comparator trial completed. Original synthetic MIPS sources
were assembled with the existing LLVM tool. A synthetic PS-X EXE supplied
each full reference range. No compiler settings or production tool code
changed. The runner called the unchanged comparator entry point and only
routed its report directory into this task's local folder.

| Case | Reference bytes | Candidate bytes | Comparator result |
| --- | --- | --- | --- |
| Identical instructions | 12 | 12 | Exit 0, exact match |
| Changed destination register | 12 | 12 | Exit 1, one differing word |
| Changed immediate constant | 12 | 12 | Exit 1, one differing word |
| Inserted instruction | 12 | 16 | Exit 2, size mismatch rejected |
| Unresolved call relocation in ELF | 16 | 16 | Exit 2, unresolved relocation rejected |
| Unresolved ELF against identical raw reference | 16 | 16 | Exit 2, unresolved relocation still rejected |

The comparison preserved each intended reference length. Nothing was
trimmed, padded, normalized or linked to evade a rejection. These results
confirm the existing comparator's safeguards on these fixtures. They do
not verify any game function.

## Timing and limits

The six objdiff processes took a median 4.12 ms, with a range of 3.91 to
5.12 ms. These are single process runs, not repeated benchmarks. The
comparator's recorded times use its in-process entry point and have a
different scope. Comparing those times would not measure review speed.

Time for a reviewer to identify the first cause with and without a viewer
was not measured. The author knew the fixtures. A controlled review test
with previously unseen cases is still needed. The object trial shows
that the viewer exposes these six expected cases. It does not establish
a speed gain, broad instruction coverage, scheduling analysis, correct
retail object recovery or support on other hosts.

## Evidence and remaining work

Local evidence is in `build/research/diff/`: `manifest.json`,
`install-preparation.json`, `install-records.json`, `attempt-ledger.json`,
`viewer-check-records.json`, retained package notices, stage logs,
`comparator-results.json`, and the synthetic fixtures. `objdiff/` holds
the official binary, digest record, help, run records and instruction
views. The initial stop
assessment and its correction are retained. The manifest records source
revision, hashes, commands, exit codes, failure stages, assembler inputs
and exact comparator outcomes. No success marker was created for R04.

```
python3 build/research/diff/check_comparator.py
python3 -m unittest discover -s tests -p test_compare.py -v
python3 tools/pr_guard.py
```

Four comparator tests passed. Six synthetic comparator cases passed their
expected outcomes. Six objdiff object checks passed. The guard passed.
All failures remain recorded by problem. Objdiff had no failed attempts.
Expected comparator rejection codes are acceptance results, not setup
attempts. No viewer process remains active.

Use objdiff as an optional local aid when trustworthy target objects exist.
Keep exact comparison authoritative for byte claims. A later raw-image
asm-differ trial needs a compatible objdump choice. Measure reviewer effort
before claiming a speed improvement. Neither viewer has been added to the
runtime, baseline checks or required project dependencies.

The coordinator independently checked the native binary digest against
the official v3.8.3 release metadata, checked the retained input, tool and
objdiff artifact hashes, reran all six object comparisons and reproduced
their complete JSON views, and reran all six exact-comparator cases.
All outcomes matched, including the unresolved self-comparison rejection.
The local `review/` folder retains that review. The coordinator made no
retail, GUI, other-host or review-speed claim.
