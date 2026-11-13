# R05 result: Compiler corpus stopped at input preparation

Date: November 13, 2026. Outcome: Failed compiler trial. The batch stopped
after three failures at the compiler stage. Reviewed by the research
coordinator on the same date.
Host: macOS 27.2.1 ARM64, Python 3.15.2.

The task contract required semantics comments inside preprocessed fixtures.
[TOOLCHAIN.md](../../TOOLCHAIN.md) requires comments to be processed before
passing `.i` input to the old compiler. The task contract was inconsistent.
The worker also assumed that cc1 would skip the comments. The files did
not meet the documented input precondition.

## Scope and tools

Root reserved the shared `build/compile/` directory before the batch. Every
compiler invocation ran serially. Each result directory was copied into
the isolated task folder immediately. The worker released the shared
directory when the three-failure stop was reached.

The selected compiler assets were GCC 2.7.2 PSX and GCC 2.8.1 PSX from
[old-gcc release 0.17](https://github.com/decompals/old-gcc/releases/tag/0.17).
Their installed binary hashes and existing download pins were recorded.
Only GCC 2.7.2 was invoked. No GCC 2.8.1 corpus run occurred.

The unchanged adapter was maspsx at
`4ffa8b5106f9780d5d4aa7609f184949433ddbbc`, with ASPSX mode 2.56 selected.
Its pinned [license is MIT](https://github.com/mkst/maspsx/blob/4ffa8b5106f9780d5d4aa7609f184949433ddbbc/LICENSE).
LLVM tools reported version 23.1.5. Their
[license is Apache 2.0 with LLVM exceptions](https://github.com/llvm/llvm-project/blob/llvmorg-23.1.5/llvm/LICENSE.TXT).
The adapter and assembler stages were never reached.

The checked old-gcc repository root had no `LICENSE` file. The embedded
compiler source notices were not independently audited in this stopped
trial. No compiler, adapter, LLVM source, or binary was redistributed.
The six original fixtures carry our GPL-3.0-or-later notice.

All compiler calls used the runner's documented flags unchanged:
`-O2 -G0 -mips1 -mcpu=3000 -msoft-float -mno-abicalls -fgnu-linker -quiet`.
No tool was installed. No retail input or display-fill variant was used.

## Actual compiler results

Six original fixtures were written under `tests/fixtures/compiler/corpus/`.
Each states its target primitive widths and expected behavior. Their hashes
were preserved. No fixture was changed after the failed runs.

| Fixture | GCC 2.7.2 | GCC 2.8.1 |
| --- | --- | --- |
| Branch with external call | Parse diagnostics, then SIGSEGV | Not run |
| Counted byte loop | Parse diagnostics, then SIGSEGV | Not run |
| Global at byte offset 0x8000 | Parse diagnostics, then SIGSEGV | Not run |
| Signed halfword loads | Not run after stop | Not run |
| Signed division with guards | Not run after stop | Not run |
| Unsigned byte stores | Not run after stop | Not run |

Each attempted fixture reported a line-1 parse error. The compiler logs
also contain malformed-looking token text. All three cc1 processes then
died with signal 11. These are separate observations: invalid prepared
input and compiler crashes. The exact parser defect was not isolated.
They do not establish that a compiler cannot build the intended source.
No comment-removal retry or alternative compiler variant was run.

There were zero successful corpus objects. Code size, stack frames,
delay slots, load hazards, hi/lo scheduling and relocations were not
measured. The planned repeat set was not run. No comparison distinguished
the two compiler versions. No claim about the retail compiler is supported.

An earlier ancillary `cc1 --version` probe also failed because that old
program does not accept the option. It was not repeated. That probe and
its observed exit code are recorded separately from the three corpus
failures. Initial per-invocation compiler timings were not retained because
the local batch helper stopped before writing its summary. The logs remain.
No timing was reconstructed or measured by rerunning the failed calls.

## Separate host semantic checks

The unchanged fixture sources compiled with Apple clang 21.0.0 as ordinary
C, with address and undefined-behavior sanitizers. Five static assertions
checked byte, short, int and unsigned-int widths and the signed minimum.
The executable passed independently prepared arithmetic and input checks:

| Case | Count |
| --- | --- |
| Signed-halfword pairs | 121 |
| Values stored as four unsigned bytes | 9 |
| Byte-loop inputs, including null with zero count | 66 |
| Branch inputs with external-call count checks | 12 |
| Guarded signed divisions | 195 |
| Values loaded at global word index 8192 | 9 |

The division reference used integer absolute values and explicit sign
application to compute truncation toward zero. It covered zero divisors
and the signed-minimum divided by negative one. Those cases are guarded
in the fixture before C division is evaluated.

This host pass checks the fixtures' intended C behavior under the asserted
primitive widths. It does not rescue the compiler trial. It supplies no
MIPS execution, target relocation, scheduling or object reproducibility
evidence. The global test used an ordinary host array and did not test a
target link address near a signed-low-half carry.

## Evidence and next work

Two compiler-runner tests and four comparator tests passed. The guard
passed after the public report was written. No game source, runner, pin, SDK
name, progress ledger or task status was changed by this worker.

All detailed evidence stays under `build/research/compiler/`:

- `manifest.json` records commands, source and tool hashes, exits and limits.
- `pass-1/2.7.2/` retains all three failed run directories and raw logs.
- `version-probe.json` records the unsupported version probe.
- `host_semantics.py`, `host-cases.c` and `host-validation.json` retain the
  separate semantic checks, including their exact commands and timings.
- `run_corpus.py` retains the stopped batch helper. Do not rerun it under
  this task or use it to bypass the three-failure stop.

The compiler runner removed its old object and success record, but left
previous adapter assembly and later-stage logs after each compiler failure.
Such copied files are marked stale and excluded from this trial. They
were not inspected as corpus assembly or used for measurements.

The safe repeat commands for the completed checks are:

```
python3 build/research/compiler/host_semantics.py
python3 -m unittest discover -s tests -p test_compile_candidate.py -v
python3 -m unittest discover -s tests -p test_compare.py -v
python3 tools/pr_guard.py
```

A separately authorized future batch first needs a consistent preparation
contract: keep documented original source and produce a distinct,
comment-free `.i` through an explicit preprocessor, preserving both hashes.
It should also clear or label every stale intermediate before a run.
The runner cleanup was fixed after this trial and validated with four
fake-tool tests. That separate fix invoked no old compiler and did not
retry these fixtures.
It can then test the six synthetic cases with fixed settings and repeat
the whole set. Do not use this failure to choose flags or compiler versions.

Only after that method passes should a separate assignment propose already
researched whole game functions with independently reviewed contiguous
ranges. Their portable source must be ours, their SDK calls must remain
named, and the stopped display-fill experiment must remain stopped.

The coordinator checked all recorded artifact and fixture hashes, checked
the three retained first-line diagnostic logs and recorded signal exits,
and independently rebuilt and ran the sanitized modern host check. Its
412 cases and five ABI assertions passed. The coordinator invoked no old
compiler. The local `review/` folder retains this review. The six source
fixtures remain unchanged, with a sidecar note explaining their invalid
prepared-input status and the three-failure stop.
