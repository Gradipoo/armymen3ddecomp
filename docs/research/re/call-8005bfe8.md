# Return at 0x8005bfe8

Traced fact from the USA PS-X EXE. Re-check on a disc you own with `python3 tools/entry_disasm.py build/disc/SLUS_004.91 --start 0x8005bfe8`. The executable and the listing stay in `build/`.

The start address is `0x8005bfe8`. The `jal` in [call-8005bfe0.md](call-8005bfe0.md) calls `CdDiskReady` and returns here. This note does not state `CdDiskReady`'s `v0`. `s0` is `0x800d89b8`. The saved `ra` is `0x8007a6bc`. The caller `s1` is 23. The frame at `0x800251f8` stays open. Its saved `ra` stays `0x8007faec`. The `0x14` bytes at `0x800d89b8` stay 0. This block has not stored `0x800d89bc`.

`addiu` at `0x8005bfe8` sets `v1` to 2. `bne` at `0x8005bfec` compares `v0` with `v1`. `v0` is not stated, so this note does not take either side. The delay slot is `nop`. The store at `0x8005c000` and the join at `0x8005c004` are not traced. The caller return at `0x8007faec` is not traced.
