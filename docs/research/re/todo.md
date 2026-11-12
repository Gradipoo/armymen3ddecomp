# To do

Open reverse engineering work. Take one item. Cite an address when you learn one. Leave raw C under `build/ghidra/`.

- Extract the local USA cue with `python tools/disc.py` into `build/disc/` and confirm a PS-X EXE.
- Read that header with `python tools/exe_info.py` (PC, GP, load address, size).
- Import it with `python tools/ghidra/import.py` when Ghidra is available (`GHIDRA_INSTALL_DIR`, then `analyzeHeadless` or `analyzeHeadless.bat`).
- Export `game-functions.tsv` in this folder: address, size, name.
- Trace the retail entry point. Add a research note with one address.
