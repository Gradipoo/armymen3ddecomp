# Local candidate builds

`tools/compile_candidate.py` runs explicit local tools. It does not install
anything or change the host CMake build. Python uses its standard library.
CI tests the runner with synthetic inputs. CI does not need these compilers.

The first working chain is:

1. GCC 2.7.2 PSX from [old-gcc release 0.17](https://github.com/decompals/old-gcc/releases/tag/0.17).
2. [maspsx](https://github.com/mkst/maspsx) at the commit in `toolchains.json`.
3. The existing LLVM 23.1.5 `llvm-mc` assembler, with MIPS I little-endian output.

The compiler archive was checked against the SHA-256 digest published with
the upstream release. The adapter is pinned by commit and archive hash.
These pins are in [toolchains.json](toolchains.json). Downloads and extracted
tools stay under `build/toolchains/`. No Sony SDK files are needed for this
synthetic test. Nothing is installed system-wide.

## Build a candidate

Use preprocessed C in an `.i` file. Headers, macros, and comments must have
already been processed. Use a suitable target preprocessor for real code.
The synthetic fixture is handwritten preprocessed C with no dependencies.
It is our code, covered by the repository license.

On the current macOS ARM64 machine, this command builds the fixture:

```
python tools/compile_candidate.py tests/fixtures/compiler/add.i --cc1 build/toolchains/gcc-2.7.2-psx/cc1 --maspsx build/toolchains/maspsx-source/maspsx-4ffa8b5106f9780d5d4aa7609f184949433ddbbc/maspsx.py --llvm-mc /opt/homebrew/opt/llvm/bin/llvm-mc --aspsx-version 2.56
```

Other machines need their own compatible tool paths. The pinned compiler
asset is a native macOS ARM64 binary. It is not a Linux or Windows binary.
The script takes arguments as a list, so paths may contain spaces.

Outputs stay under `build/compile/`:

- `compiler.s` and `assembler.s`: local assembly.
- `candidate.o`: ELF32 MIPS candidate.
- Stage logs.
- `provenance.json`: exact commands, flags, source hash, tool hashes, adapter
  Python file hashes, and object hash.

A new run invalidates the previous success record and object first. Failed
stages stop the run. Inspect the stage log before retrying. No ledger status
changes automatically.

The default flags are `-O2 -G0 -mips1 -mcpu=3000 -msoft-float -mno-abicalls
-fgnu-linker -quiet`. They are experimental settings. To replace the whole
list, repeat `--compiler-flag=VALUE` for each desired argument. The ASPSX
version must be explicit. The assembler is LLVM, rather than the original
ASPSX or GNU assembler. Wider compatibility still needs testing.

## First smoke result

On November 13, 2026, the fixture compiled to two instructions: return through
`ra`, with an unsigned addition into `v0` in the delay slot. The section was
exactly eight bytes. Those bytes were checked against an independently
specified encoding of those two instructions in a synthetic PS-X EXE.
The comparison returned an exact match. All inputs were synthetic.

This establishes that the local pipeline works for this case. It does not
identify the retail compiler, its flags, its assembler, or its SDK version.
It does not verify game behavior. Many toolchains can produce this function.

The next calibration must use researched retail boundaries and our own C.
Check several cases with branches, loads, stores, and calls before drawing
a conclusion about the original toolchain. Keep retail outputs local and
record the supported conclusions in notes. Follow the existing boot path
and named-call rules. Do not enter a known SDK body for calibration.

## Retail calibration status

The display-fill comparison has stopped after three failed attempts. The
controlled GCC 2.8.1 experiment retained the same source and flags as the
GCC 2.7.2 attempt. It produced 160 bytes against a 152-byte reference.
See [the calibration record](research/re/calibration-80076274.md). Neither
compiler is confirmed as the retail compiler. The original synthetic
smoke test still uses GCC 2.7.2.
