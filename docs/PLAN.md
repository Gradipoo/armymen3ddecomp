# Plan

Agents read this roadmap. They do not rewrite it in a normal gap change. Edit it when the user asks for a roadmap change.

## Goal

A public decomp of Army Men 3D, PlayStation USA release, serial SLUS-00491, on Linux, macOS, and Windows.

The program is new code. It reads a disc the user owns. Retail behavior is checked with a local Ghidra project of that disc. The repo ships our code. The user supplies the disc. Raw decompiled C stays untracked.

This project is not affiliated with 3DO.

## Milestone

1. Docs, license, and ignore rules.
2. Compare tools: disc extract, EXE info, Ghidra import, gap list, and `pr_guard`.
3. A small CMake program, with no third-party libraries, and one `// gap:` each for executable load, keyboard, server browser, and mods.
4. The same checks on Linux, macOS, and Windows. Tests, `python tools/pr_guard.py`, and a CMake build. Those checks have no disc and no Ghidra.

After that, close one gap at a time.

## How a gap is closed

1. Run `python tools/gaps.py`.
2. Pick one `// gap:`, or one function in `docs/research/re/game-functions.tsv` that the notes do not cite yet.
3. Decompile that function on your machine. The C stays under `build/ghidra/`.
4. Write our code.
5. Add a research note that cites the address.
6. Run `python tools/pr_guard.py`.

One gap per change. Stop after three failed attempts at the same problem.

## Tools

Python 3, standard library. Invoke them as `python tools/...`.

- `python tools/disc.py` reads a BIN/CUE. Track 1 is MODE2/2352. It extracts ISO9660 into `build/disc/`. The cue path comes from the argument or from `AM3D_DISC`.
- `python tools/exe_info.py` checks the PS-X EXE header and prints PC, GP, load address, and size.
- `python tools/ghidra/import.py` strips the 2048-byte header, imports the text as MIPS little-endian at the load address, and runs a post-script. Ghidra is found from `GHIDRA_INSTALL_DIR`, then `analyzeHeadless` on Unix and `analyzeHeadless.bat` on Windows. The project is `tools/ghidra/project/`.
- `tools/ghidra/scripts/ExportFunctions.java` writes `docs/research/re/game-functions.tsv` with address, size, and name only.
- `tools/ghidra/scripts/DecompileAt.java` writes one function's C under `build/ghidra/`.
- `python tools/gaps.py` lists `// gap:` hits and TSV functions the notes do not cite yet.
- `python tools/pr_guard.py` fails the tree on a cue, bin, iso, PS-X EXE, Ghidra project, or `*.decomp.c`.

Ghidra is optional. If it is missing, the import tool prints an install hint for that OS and exits. We do not install it.

Tests use synthetic headers and cues, never the real disc: `tests/test_exe_header.py`, `tests/test_cue.py`, `tests/test_pr_guard.py`. Run them with `python -m unittest`.

## Flow

The local cue goes through `disc.py` into a PS-X EXE under `build/`. Ghidra import writes `game-functions.tsv` and untracked C under `build/ghidra/`. `gaps.py` reads the TSV and the `// gap:` comments. An agent picks one gap, reads the local C, and writes our code plus a research note.

## Where the program grows

Each of these files stays small and carries one `// gap:`:

- `components/exe/load.cpp`: where the retail entry point will be traced.
- `components/input/keyboard.cpp`: keyboard.
- `components/net/browser.cpp`: server list.
- `components/mods/overlay.cpp`: a local `mods/` directory searched before the disc.

## Future lanes

Keyboard, a server browser, and mods are intentional differences from the PlayStation game. They are not started.

See [research/re/deviations.md](research/re/deviations.md).

## Leave this file alone when

- You are closing one gap.
- You are adding a research note for one address.
- You are fixing a tool bug that leaves the roadmap the same.

## First milestone is done when

- `python -m unittest` passes.
- `python tools/pr_guard.py` passes on a clean tree and fails when a `.bin` is added.
- CMake configures and builds the stub.
- A local `disc.py` run against the USA cue finds a PS-X EXE, with output only under `build/`.
- Keyboard, the server browser, and mods stay documented gaps.
