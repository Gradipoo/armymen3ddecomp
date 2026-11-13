# To do

Open reverse engineering work. Take one item. Cite an address when you learn one. Leave raw C under `build/ghidra/`.

- Extract the local USA cue with `python tools/disc.py` into `build/disc/` and confirm a PS-X EXE. See [exe-header.md](exe-header.md).
- Read that header with `python tools/exe_info.py` (PC, GP, load address, size). See [exe-header.md](exe-header.md).
- Import it with `python tools/ghidra/import.py` when Ghidra is available (`GHIDRA_INSTALL_DIR`, then `analyzeHeadless` or `analyzeHeadless.bat`).
- Export `game-functions.tsv` in this folder: address, size, name.
- Trace the retail entry body at `0x8007f9f8`. The header is in [exe-header.md](exe-header.md). The body is still open. That note does not close the gap in `components/exe/load.cpp`.

- Continue this boot at `0x80025390` after the display-clear loop returns. See [call-8007641c-second.md](call-8007641c-second.md).
