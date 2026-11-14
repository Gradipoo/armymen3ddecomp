# Call at 0x8005bfe0

Traced fact from the USA PS-X EXE. Re-check on a disc you own with `python3 tools/entry_disasm.py build/disc/SLUS_004.91 --start 0x8005bfe0`. The executable and the listing stay in `build/`.

The start address is `0x8005bfe0`. The `jal` in [call-8005bfd0.md](call-8005bfd0.md) calls `CdControlB` and returns here. This note does not state `CdControlB`'s `v0`. `s0` is `0x800d89b8`. The saved `ra` is `0x8007a6bc`. The caller `s1` is 23. The frame at `0x800251f8` stays open. Its saved `ra` stays `0x8007faec`.

`jal` at `0x8005bfe0` targets `0x8008428c`. `tools/sdk_names.txt` names that address `CdDiskReady`. `ra` becomes `0x8005bfe8`. The delay slot sets `a0` to 1. This note does not enter that body.

The next note starts at `0x8005bfe8`. The caller return at `0x8007faec` is not traced.
