# Call at 0x8008dae4

Traced fact from the USA PS-X EXE. Re-check on a disc you own with `python3 tools/entry_disasm.py build/disc/SLUS_004.91 --start 0x8008dae4`. The executable and the listing stay in `build/`.

The start address is `0x8008dae4`. The `jal` in [call-8008dadc.md](call-8008dadc.md) calls `StartCARD` and returns here. This note does not state `a0` after `StartCARD` returns. It does not state `v0`. The saved `ra` is `0x8007c314`. The caller `s1` is 20. The frame at `0x800251f8` stays open. Its saved `ra` stays `0x8007faec`.

`jal` at `0x8008dae4` targets `0x8008db1c`. `tools/sdk_names.txt` names that address `_bu_init`. `ra` becomes `0x8008daec`. The delay slot is `nop`. This note does not enter that body.

The next note starts at `0x8008daec`. The caller return at `0x8007faec` is not traced.
