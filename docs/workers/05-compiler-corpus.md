# R05: Compiler fingerprint corpus

Status: Failed setup trial. Stopped after three compiler-stage failures.
Reviewed November 13, 2026. See the [result](results/compiler-corpus.md).
No fourth compiler invocation is authorized under this task.

## Question and scope

Which code shapes distinguish our two installed compiler versions, and
which differences come from maspsx or the assembler? Build a synthetic
corpus before another retail calibration. Read `docs/TOOLCHAIN.md` and
the [maspsx behavior table](https://github.com/mkst/maspsx#known-differences).
That table gives test leads, not proof of Army Men's assembler version.

Permitted public files: `docs/workers/results/compiler-corpus.md` and
original fixtures under `tests/fixtures/compiler/corpus/`.
Permitted local directory: `build/research/compiler/`.
Do not edit compiler runners, pins, flags, or the stopped retail candidate.
Read `docs/WORKERS.md`.

## Inputs and commands

```
python3 tools/compile_candidate.py --help
python3 -m unittest discover -s tests -p test_compile_candidate.py -v
python3 -m unittest discover -s tests -p test_compare.py -v
python3 tools/pr_guard.py
```

Use `tools/compile_candidate.py` with explicit installed cc1, maspsx and
llvm-mc paths from `docs/TOOLCHAIN.md`. Fix the current documented flags
and ASPSX 2.56 for the baseline. Run each source with installed GCC 2.7.2
and 2.8.1 only. Copy each run's outputs and provenance immediately into its
own task subdirectory because the runner reuses `build/compile/`.
Do not run the shared compile runner concurrently with another worker.
Coordinate its use with the parent before starting.

## Acceptance and evidence

Write six tiny original preprocessed C fixtures: signed halfword loads,
unsigned byte stores, a counted loop, a branch with an external call,
signed division, and a global address near a 16-bit carry boundary.
Use explicit fixed-width primitive assumptions appropriate for these
compilers. Avoid undefined shifts, overflow, aliasing and uninitialized
values. Keep expected semantics in a separate `README.md`. Feed only
comment-free, preprocessed `.i` inputs to cc1, as `docs/TOOLCHAIN.md`
requires. Record the preprocessor command and source/output hashes.

Correction, November 13, 2026: the original task incorrectly requested
comments inside handwritten `.i` fixtures. The worker's compiler batch
stopped after three failures. This corrected instruction is not a retry
authorization. Preserve those failed inputs and logs. A later batch needs
a separately reviewed assignment after the stopped result is reported.

Both compilers should build all six, or record failures. Repeat one whole
set and require identical object hashes for reproducibility. Tabulate
code size, frame size, delay slots, load hazards, hi/lo scheduling and
symbol relocations for each version. Explain any assembler rejection
before calling a compiler incompatible. Do not compare unresolved bytes
as if linked calls were final instructions.

Record independent source encodings or arithmetic checks where feasible.
An assembly round trip tests output handling, not source behavior. Identify
at least two fixtures where outputs differ, or state that the corpus did
not distinguish the versions. No retail compiler is identified by this
trial. Propose a later separately assigned corpus of already researched,
reviewed whole game functions. Do not run it in this task.

## Known failure modes

An unchanged source and flags do not isolate the assembler. Small constant
functions can be identical across many compilers. Calls and globals need
consistent placement. Do not trim, pad, mask, or permute to force a match.
The three failed attempts at 0x80076274 remain stopped.
