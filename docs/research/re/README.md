# Research notes

Notes in this folder describe the PlayStation USA executable, serial SLUS-00491. Quote one address. Raw decompiled C stays under `build/ghidra/`. It is never committed.

| File | Contents |
| --- | --- |
| [todo.md](todo.md) | Open research work |
| [unverified.md](unverified.md) | Claims waiting for a second check on a disc you own |
| [deviations.md](deviations.md) | Keyboard, server browser, and mods. Not started. |
| [exe-header.md](exe-header.md) | PS-X EXE header at `0x8007f9f8`. Body not traced. |
| game-functions.tsv | Function facts from the Ghidra export: address, size, name |

The TSV appears here after Ghidra export. `python tools/gaps.py` compares `// gap:` comments and that TSV with these notes.

A normal gap change may add a note here. It leaves [docs/PLAN.md](../../PLAN.md) alone.
