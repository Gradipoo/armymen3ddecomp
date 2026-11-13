# Army Men 3D decomp

A new program that reads an Army Men 3D disc you own. The behavior reference is the PlayStation USA release, serial SLUS-00491. This project is not affiliated with 3DO.

Retail code is the behavior reference. You read it in Ghidra on your own machine. This repo holds our code. You supply the disc. Raw decompiled C is never committed.

## Help me contribute. Follow AGENTS.md.

Say that to an agent, or read [AGENTS.md](AGENTS.md) and [CONTRIBUTING.md](CONTRIBUTING.md) yourself.

Three ways in, once the matching piece exists:

1. Play and report, once a launcher exists.
2. Trace a claim against the local executable.
3. Fix or port one gap.

A gap is a named hole in our code, marked `// gap:`. One gap per change.

## Platforms

Linux, macOS, and Windows. Our Python tools use the standard library. The default CMake build has no third-party runtime libraries. An optional SDL2 platform test is described in [docs/PLATFORM.md](docs/PLATFORM.md).

```
python tools/disc.py
python tools/exe_info.py
python tools/ghidra/import.py
python tools/gaps.py
python tools/boot_slice.py
python tools/progress.py
python tools/pr_guard.py
```

Pass the cue path to `python tools/disc.py`, or set `AM3D_DISC`. Extracts go to `build/disc/`. The Ghidra project goes to `tools/ghidra/project/`. One function's C goes under `build/ghidra/`.

Function facts go in `docs/research/re/game-functions.tsv`: address, size, and name only.

`python tools/boot_slice.py` needs the local PS-X EXE and `--start ADDRESS`. It writes one boot slice to `build/boot-slice.txt`. A named SDK call, BIOS A/B/C call, or address that already has a call note is recorded and not entered. A known conditional branch is followed. An unknown branch, an unnamed call, `jr`, or 64 instructions ends the slice. Pass `--max` to raise that cap in the local report. Pass `--ra` for the entry value of `ra`. A save and reload through `sp` keeps it. An unnamed target inside the executable is entered, and `jr` back to the return address resumes the caller. A named call is not entered. A stored word can satisfy a later load. `word_fill` and `bzero` hide their range.

`python tools/pr_guard.py` fails the tree if a cue, bin, iso, PS-X EXE, Ghidra project, or decompiled C is present.

Ghidra is optional. Set `GHIDRA_INSTALL_DIR` when you want to read the executable. The import tool looks there first, then for `analyzeHeadless`, or `analyzeHeadless.bat` on Windows. If Ghidra is missing, the tool prints a hint for your OS and exits.

Function status and evidence are tracked separately from citations. See [docs/PROGRESS.md](docs/PROGRESS.md).
Local candidate code can be checked against the executable. See [docs/COMPARE.md](docs/COMPARE.md).
Optional local compiler tools and the synthetic smoke test are described in [docs/TOOLCHAIN.md](docs/TOOLCHAIN.md).
One-range disassembly and local C drafts are described in [docs/ANALYSIS.md](docs/ANALYSIS.md).

Reuse candidates and their adoption checks are listed in [docs/REUSE.md](docs/REUSE.md).

## Roadmap

[docs/PLAN.md](docs/PLAN.md) is the roadmap. Agents read it. A normal gap change leaves it alone.

Keyboard, a server browser, and mods are future lanes. They are not started. Mods means a local `mods/` directory searched before the disc. See [docs/research/re/deviations.md](docs/research/re/deviations.md).

## License

Our code is GPL-3.0-or-later. See [LICENSE](LICENSE) and [LEGAL.md](LEGAL.md).
