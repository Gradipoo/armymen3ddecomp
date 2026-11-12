# Next

Later agents follow this file. Leave [PLAN.md](PLAN.md) alone. This is a prototype. The next step is small. It is not a playable port.

## Goal

Turn the `am3d` program into a launcher that checks a disc you own. Record the PS-X EXE header as a research fact. The retail entry body stays untraced. Keyboard, the server browser, and mods stay gaps.

Two agents can take the two tasks below. They edit different files.

## Already true

The scaffold commit is `cdf5712254743bd8932f00b7661a2666fec96fac`. The working tree was clean. Nothing has been pushed. `gh` auth for Gradipoo is invalid. Do not push. Do not create a GitHub repo.

A local extract wrote `build/disc/SLUS_004.91`. It is a PS-X EXE. The header tool reports:

```
pc=0x8007f9f8
gp=0x00000000
load=0x80010000
text_size=0x000b5800
text_offset=0x800
```

The entry address is the pc, `0x8007f9f8`. The load address is `0x80010000`. The text size is `0x000b5800`. Our tool treats the text as starting at file offset `0x800`. The entry bytes sit at file offset `0x701f8`, which is `0x800 + (0x8007f9f8 - 0x80010000)`.

Ghidra is not installed. Do not install it. Do not add dependencies.

On this machine the interpreter is `python3`. `python` is not on PATH. CI installs Python and calls `python`. Commands in this file use `python3`.

The USA disc stays in `Army Men 3D (USA)/`. That folder is gitignored. Extracted files stay in `build/`. That directory is gitignored.

Never commit or upload:

- game files, the cue, the bin, the iso, or the executable
- extracted assets
- `build/`
- the Ghidra project (`tools/ghidra/project/`)
- decompiled C (`build/ghidra/`, `*.c.ghidra`, `*.decomp.c`)
- a disassembly dump of the retail text

Quoting one address is fine. Do not quote retail strings or file dumps.

## Launcher

Turn the existing `am3d` executable into a launcher. Use the C++ standard library only. Add no libraries.

Change `src/main.cpp` only. Leave `CMakeLists.txt` as it is. The `am3d` target is already there. Leave these files as they are, including each gap comment:

- `components/exe/load.cpp`
- `components/input/keyboard.cpp`
- `components/net/browser.cpp`
- `components/mods/overlay.cpp`

`src/main.cpp` may keep the four status calls so those objects stay linked. The calls stay gaps. They are not features.

Behavior:

1. Read the cue path from the first argument. If that argument is absent, use `AM3D_DISC`.
2. Find `tools/disc.py` by walking up from the current directory and from the executable until the script exists. Pass absolute paths so the working directory does not matter.
3. Run that script with `python3`. If `python3` is missing, use `python`. Pass the cue path when the user gave one. When the user gave none, pass no cue argument and let the script read `AM3D_DISC`. Do not pass `--out`. The script writes under `build/disc/` only.
4. If the script exits non-zero, exit 1 and keep its stderr. With no cue and no `AM3D_DISC`, that line is `error: pass a cue path or set AM3D_DISC`. When the path is not a file, that line is `error: cue not found:` plus the path.
5. Find a file under `build/disc/` whose first 8 bytes are `PS-X EXE`. On the USA disc that file is `build/disc/SLUS_004.91`. This read is only the check that picks the file. Then run `tools/exe_info.py` on it, with the same interpreter.
6. Exit 0 only when `exe_info.py` exits 0. Let its header lines through on stdout.
7. If no PS-X EXE is found, print `error: no PS-X EXE in build/disc` to stderr and exit 1.
8. If a tool fails, exit 1. If you use `std::system`, turn a failed wait status into exit code 1. Do not return the raw wait status.

Quote the cue path when you spawn a tool. The disc folder name contains spaces.

The launcher does not open a window. It does not open a socket. It does not write extracted files outside `build/`.

Do not add a unit test that runs `am3d`. CI runs the Python tests before the build, and those tests have no disc.

Keyboard, the server browser, and mods stay gaps.

## Decomp

This slice does not need Ghidra. Do not paste retail code.

Add `docs/research/re/exe-header.md`. Record these fields:

- address: `0x8007f9f8`
- pc: `0x8007f9f8`
- load: `0x80010000`
- size: `0x000b5800`

Say that the body at that address is not yet traced. Cite `0x8007f9f8`. Do not paste instruction words or retail strings.

Add a row for the new note in `docs/research/re/README.md`.

Add one claim in `docs/research/re/unverified.md`:

- Address: `0x8007f9f8`
- Claim: pc `0x8007f9f8`, load `0x80010000`, text size `0x000b5800`
- Re-check: `python3 tools/exe_info.py build/disc/SLUS_004.91`

In `docs/research/re/todo.md`, point the extract bullet and the header bullet at the new note. Leave the Ghidra import bullet. Leave the entry body open. This note does not close the gap in `components/exe/load.cpp`. Closing that gap waits until the body is traced and our code exists.

Re-check command, after a local extract:

```
python3 tools/exe_info.py build/disc/SLUS_004.91
```

Expected lines:

```
pc=0x8007f9f8
gp=0x00000000
load=0x80010000
text_size=0x000b5800
text_offset=0x800
```

The note records address, pc, load, and size. `gp` and `text_offset` are the tool's check that the file is still the same header.

Optional step, same research agent: a local disasm of the first four instructions at the entry point. Add `tools/entry_disasm.py` only if you do this step. Python 3 standard library only. Read the header the same way `tools/exe_info.py` does. Decode four little-endian MIPS instructions at file offset `0x701f8`. Write them to `build/entry-disasm.txt`. Do not commit that file. Do not copy those lines into the note. The note still says the body is not yet traced, and it cites `0x8007f9f8`.

Command:

```
python3 tools/entry_disasm.py build/disc/SLUS_004.91
```

Expected: exit 0, and `build/entry-disasm.txt` exists. `git check-ignore -v build/entry-disasm.txt` matches the `build/` rule. `git status` does not list the file.

## What not to do

- Do not add SDL or any other library.
- Do not download or install Ghidra.
- Do not push, and do not create a GitHub repo.
- Do not commit game data, the executable, extracted assets, or a disassembly dump.
- Do not match or decompile the whole exe.
- Do not edit `docs/PLAN.md`.
- Do not implement keyboard, the server browser, or mods.
- Do not remove the gap comments in the four component files.
- Do not open a window or a socket.

## Done

Launcher, from the repo root. Unset `AM3D_DISC` for the first two runs.

```
cmake -S . -B build
cmake --build build
./build/am3d
./build/am3d does-not-exist.cue
./build/am3d "$AM3D_DISC"
python3 tools/exe_info.py build/disc/SLUS_004.91
python3 -m unittest discover -s tests
python3 tools/pr_guard.py
python3 tools/gaps.py
```

Expected:

- The build writes `build/am3d`. On Windows, with the Visual Studio generator, the binary is `build\Debug\am3d.exe`.
- `./build/am3d` with no cue and no `AM3D_DISC` exits 1. stderr is `error: pass a cue path or set AM3D_DISC`.
- `./build/am3d does-not-exist.cue` exits 1. stderr is `error: cue not found: does-not-exist.cue`.
- `./build/am3d "$AM3D_DISC"` exits 0 when `AM3D_DISC` is the USA cue. stdout includes `pc=0x8007f9f8`.
- `exe_info.py` prints the five lines in the Decomp section.
- Unit tests pass.
- `pr_guard.py` passes.
- `gaps.py` still lists the gap comments in `components/exe/load.cpp`, `components/input/keyboard.cpp`, `components/net/browser.cpp`, and `components/mods/overlay.cpp`.

Research note:

- `docs/research/re/exe-header.md` has address `0x8007f9f8`, pc `0x8007f9f8`, load `0x80010000`, and size `0x000b5800`.
- The note says the body is not yet traced.
- `python3 tools/pr_guard.py` passes.
- `git status` shows no file from `build/` and no file from `Army Men 3D (USA)/`.

Optional disasm, when that step is taken:

```
python3 tools/entry_disasm.py build/disc/SLUS_004.91
git check-ignore -v build/entry-disasm.txt
git status --short
```

Expected: the script exits 0, the ignore check names `build/`, and status does not list `build/entry-disasm.txt`.

## Split

Launcher agent. Edit `src/main.cpp` only.

Research agent. Edit these files:

- `docs/research/re/exe-header.md` (new)
- `docs/research/re/README.md`
- `docs/research/re/unverified.md`
- `docs/research/re/todo.md`

The optional disasm adds `tools/entry_disasm.py` and writes `build/entry-disasm.txt`. The research agent owns that script. The launcher agent does not.

Neither agent edits `docs/PLAN.md`, `docs/NEXT.md`, `CMakeLists.txt`, `components/`, `tools/disc.py`, `tools/exe_info.py`, `tools/pr_guard.py`, `tools/gaps.py`, or `.github/workflows/ci.yml`.
