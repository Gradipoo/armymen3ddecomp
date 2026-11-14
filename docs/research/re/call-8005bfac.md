# Call at 0x8005bfac

Traced fact from the USA PS-X EXE. Re-check on a disc you own with `python3 tools/entry_disasm.py build/disc/SLUS_004.91 --start 0x8005bfac`. The executable and the listing stay in `build/`.

The start address is `0x8005bfac`. The `jal` in [call-8005bfa4.md](call-8005bfa4.md) calls `CdInit` and returns here. This note does not state `CdInit`'s `v0`. `s0` is `0x800d89b8`. The saved `ra` is `0x8007a6bc`. The caller `s1` is 23. The frame at `0x800251f8` stays open. Its saved `ra` stays `0x8007faec`.

`lui` at `0x8005bfac` sets `a0` to `0x80060000`. `jal` at `0x8005bfb0` targets `0x80081a40`. `tools/sdk_names.txt` names that address `CdSyncCallback`. `ra` becomes `0x8005bfb8`. The delay slot subtracts `0x425c` from `a0`, so `a0` is `0x8005bda4`. This note does not enter that body.

The next note starts at `0x8005bfb8`. The caller return at `0x8007faec` is not traced.
