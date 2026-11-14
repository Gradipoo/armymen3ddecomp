# Call at 0x8005bfc4

Traced fact from the USA PS-X EXE. Re-check on a disc you own with `python3 tools/entry_disasm.py build/disc/SLUS_004.91 --start 0x8005bfc4`. The executable and the listing stay in `build/`.

The start address is `0x8005bfc4`. The `jal` in [call-8005bfb8.md](call-8005bfb8.md) calls `CdDataCallback` and returns here. This note does not state `CdDataCallback`'s `v0`. `s0` is `0x800d89b8`. The saved `ra` is `0x8007a6bc`. The caller `s1` is 23. The frame at `0x800251f8` stays open. Its saved `ra` stays `0x8007faec`.

`lui` at `0x8005bfc4` sets `a0` to `0x80060000`. `jal` at `0x8005bfc8` targets `0x80081a54`. `tools/sdk_names.txt` names that address `CdReadyCallback`. `ra` becomes `0x8005bfd0`. The delay slot subtracts `0x4204` from `a0`, so `a0` is `0x8005bdfc`. This note does not enter that body.

The next note starts at `0x8005bfd0`. The caller return at `0x8007faec` is not traced.
