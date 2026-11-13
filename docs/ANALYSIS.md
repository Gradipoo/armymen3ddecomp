# Local function preparation

`tools/prepare_function.py` prepares one reviewed code range with spimdisasm
and m2c. It uses Python's standard library to run optional external tools.
It does not install tools, upload data, edit our source, write notes, or
advance the progress ledger.

## Local environment

Use a separate Python environment under the ignored `build/` directory.
The tested host is macOS ARM64 with Python 3.12. On Unix-like systems:

```
python3.12 -m venv build/analysis/venv
build/analysis/venv/bin/python -m pip install --cache-dir build/analysis/pip-cache -r docs/analysis-requirements.txt
```

On Windows, use an installed compatible Python to create the environment
and its `Scripts/python.exe` to install the same requirements. This is not
a system-wide installation. No disc is needed for setup. Do not put disc
files, generated assembly, or C into a package or upload service.

The selected versions are spimdisasm 1.42.4, splat64 0.50.1, and m2c at
commit `c632946b8cfbe8fce442b522dba92dfa72f1f317`. m2c's package version alone
does not identify that commit. Dependencies and source download hashes from
the tested install are in [analysis-tools.json](analysis-tools.json).
The requirements pin package versions. The recorded platform-specific
artifact hashes are provenance, not a universal wheel lock. Other hosts
and build-system dependencies need their own checks.

spimdisasm and splat declare MIT licenses. m2c declares GPL-3.0-only.
They remain external tools with their upstream notices and dependencies.
No tool source or installed package is copied into our runtime.

## Prepare a reviewed range

```
python tools/prepare_function.py build/disc/SLUS_004.91 --address ADDRESS --size SIZE
```

ADDRESS is a virtual address. SIZE is the reviewed contiguous byte count.
Both must be word-aligned. The size is limited to 256 bytes, or 64
instructions. Use a smaller range when the note rules require it. Ghidra
body sizes are address counts and do not prove a contiguous function.

The helper finds the local environment by default. Use `--python PATH`
for another analysis environment. Supply preprocessed C declarations with
`--context PATH`. The helper copies them into the local task folder and
disables m2c's context cache. Keep confirmed types separate from guesses.

Use `--llvm-mc PATH` to assemble the disassembler's output and compare it
with the selected bytes. This requires an LLVM assembler with MIPS I
support. The helper supplies assembler metadata and absolute bindings for
external symbols; it does not change generated instructions, trim padding,
mask differences, or accept unresolved relocations.

Ranges containing an SDK entry already named by our matcher are rejected
before analysis.
At call sites, known SDK names are applied through a symbol CSV. Repeated
SDK names get distinct local aliases. Indirect calls keep unknown targets.
The helper does not enter callees or infer register values at runtime.

## Outputs and limits

Each range uses `build/analysis/functions/ADDRESS/`:

- Raw code and disassembled assembly.
- A local m2c C draft and optional type context.
- Tool logs and, when requested, a round-trip assembly object.
- `task.json` with input hashes, commands, installed tool versions, static
  call targets, link registers, return addresses, and round-trip result.

A new attempt removes the old task record and C draft first. Failed stages
do not leave a successful record. A failed draft is retained as a local
diagnostic text file. Check the current exit code and hashes when reviewing
artifacts. Generated C is never ready-to-commit source.

The disassembler's PSYQ mode and m2c's little-endian GCC mode are explicit
analysis choices. They do not identify the original compiler. m2c may
infer wrong types, omit declarations, or fail on an incomplete range.
Review the instructions and use confirmed context before writing our code.

The static call list does not establish the path this boot takes. Follow
AGENTS.md for notes: stop at an unnamed call or the instruction cap, record
named calls without entering their bodies, and preserve existing notes.

An exact disassembly round trip checks that the exporter preserves bytes.
It does not verify generated C or a reconstructed game function. The helper
does not restart the stopped display-fill compiler experiment.

## First adoption check

The parent display-loop range was checked locally on November 13, 2026.
spimdisasm's assembly rebuilt to the exact selected 104 bytes. m2c produced
a C draft. The outputs and result stay under `build/analysis/functions/`.
This is one successful range, not validation of every instruction or an
executable-wide code/data split. splat is installed for later segmentation
work, but no full-game segment map has been established.

Public tests use synthetic bytes to check range limits, call metadata,
external symbol binding, and refusal to prepare named SDK bodies. They
do not need the analysis environment or a game disc.

An optional integration test exercises the real tools with an original
synthetic wrapper and a zero-filled SDK target. It checks naming without
decoding the callee. Set `AM3D_ANALYSIS_PYTHON` to the local environment's
Python and optionally `AM3D_LLVM_MC` to a MIPS-capable LLVM assembler, then
run `python -m unittest discover -s tests -p test_prepare_function.py`.
Without that environment, this test is skipped rather than reported as
a successful external-tool check.
