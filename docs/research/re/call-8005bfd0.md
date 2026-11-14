# Call at 0x8005bfd0

Traced fact from the USA PS-X EXE. Re-check on a disc you own with `python3 tools/entry_disasm.py build/disc/SLUS_004.91 --start 0x8005bfd0`. The executable and the listing stay in `build/`.

The start address is `0x8005bfd0`. The `jal` in [call-8005bfc4.md](call-8005bfc4.md) calls `CdReadyCallback` and returns here. This note does not state `CdReadyCallback`'s `v0`. `s0` is `0x800d89b8`. The saved `ra` is `0x8007a6bc`. The caller `s1` is 23. The frame at `0x800251f8` stays open. Its saved `ra` stays `0x8007faec`.

`addiu` at `0x8005bfd0` sets `a0` to 1. `addu` at `0x8005bfd4` clears `a1`. `jal` at `0x8005bfd8` targets `0x80081cd8`. `tools/sdk_names.txt` names that address `CdControlB`. `ra` becomes `0x8005bfe0`. The delay slot copies `a1` into `a2`, so `a2` is 0. This note does not enter that body.

The next note starts at `0x8005bfe0`. The caller return at `0x8007faec` is not traced.
