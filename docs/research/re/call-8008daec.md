# Return at 0x8008daec

Traced fact from the USA PS-X EXE. Re-check on a disc you own with `python3 tools/entry_disasm.py build/disc/SLUS_004.91 --start 0x8008daec`. The executable and the listing stay in `build/`.

The start address is `0x8008daec`. The `jal` in [call-8008dae4.md](call-8008dae4.md) calls `_bu_init` and returns here. This note does not state `_bu_init`'s `v0`. The saved `ra` is `0x8007c314`. The caller `s1` is 20. The frame at `0x800251f8` stays open. Its saved `ra` stays `0x8007faec`.

`lw` at `0x8008daec` loads `ra` from `sp+0x10`. `addiu` at `0x8008daf0` adds `0x18` to `sp`. `jr` at `0x8008daf4` returns through `ra`. The delay slot is `nop`. `ra` leaves as `0x8007c314`. Control goes to `0x8007c314`. That arrival is the next note. The caller return at `0x8007faec` is not traced.
