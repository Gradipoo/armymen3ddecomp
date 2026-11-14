# Call at 0x8005bfa4

Traced fact from the USA PS-X EXE. Re-check on a disc you own with `python3 tools/entry_disasm.py build/disc/SLUS_004.91 --start 0x8005bfa4`. The executable and the listing stay in `build/`.

The start address is `0x8005bfa4`. The `jr` in [call-8007f920-19.md](call-8007f920-19.md) returns here. This note does not state `a0` after that fill. It does not state `v0` beyond the fill's return `v0`, which this instruction does not read. `s0` is `0x800d89b8`. The saved `ra` is `0x8007a6bc`. The saved `s0` is `0x80010054`. The caller `s1` is 23. The frame at `0x800251f8` stays open. Its saved `ra` stays `0x8007faec`.

`jal` at `0x8005bfa4` targets `0x8008176c`. `tools/sdk_names.txt` names that address `CdInit`. `ra` becomes `0x8005bfac`. The delay slot is `nop`. This note does not enter that body.

The next note starts at `0x8005bfac`. The caller return at `0x8007faec` is not traced.
