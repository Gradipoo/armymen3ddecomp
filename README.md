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

Linux, macOS, and Windows. Tools are Python 3, standard library only. The program builds with CMake and no third-party libraries.

```
python tools/disc.py
python tools/exe_info.py
python tools/ghidra/import.py
python tools/gaps.py
python tools/pr_guard.py
```

Pass the cue path to `python tools/disc.py`, or set `AM3D_DISC`. Extracts go to `build/disc/`. The Ghidra project goes to `tools/ghidra/project/`. One function's C goes under `build/ghidra/`.

Function facts go in `docs/research/re/game-functions.tsv`: address, size, and name only.

`python tools/pr_guard.py` fails the tree if a cue, bin, iso, PS-X EXE, Ghidra project, or decompiled C is present.

Ghidra is optional. Set `GHIDRA_INSTALL_DIR` when you want to read the executable. The import tool looks there first, then for `analyzeHeadless`, or `analyzeHeadless.bat` on Windows. If Ghidra is missing, the tool prints a hint for your OS and exits.

## Roadmap

[docs/PLAN.md](docs/PLAN.md) is the roadmap. Agents read it. A normal gap change leaves it alone.

Keyboard, a server browser, and mods are future lanes. They are not started. Mods means a local `mods/` directory searched before the disc. See [docs/research/re/deviations.md](docs/research/re/deviations.md).

## License

Our code is GPL-3.0-or-later. See [LICENSE](LICENSE) and [LEGAL.md](LEGAL.md).
