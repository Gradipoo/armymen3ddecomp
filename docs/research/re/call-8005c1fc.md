# Second VSync at 0x8005c1fc

Traced fact from the USA PS-X EXE. Re-check on a disc you own with `python3 tools/entry_disasm.py build/disc/SLUS_004.91 --start 0x8005c1fc`. The executable and the listing stay in `build/`.

The start address is `0x8005c1fc`. The first `VSync` returns here. `s0` is 1. `s1` is `0x800e54e0`. The saved `ra` is `0x8005c804`. This note does not read `v0`.

`jal` at `0x8005c1fc` targets `0x8008549c`. `tools/sdk_names.txt` names that address `VSync`. `ra` becomes `0x8005c204`. The delay slot clears `a0`. This note does not enter that body. The return is the next note.
