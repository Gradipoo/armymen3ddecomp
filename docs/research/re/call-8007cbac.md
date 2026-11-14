# Return at 0x8007cbac

Traced fact from the USA PS-X EXE. Re-check on a disc you own with `python3 tools/entry_disasm.py build/disc/SLUS_004.91 --start 0x8007cbac`. The executable and the listing stay in `build/`.

The start address is `0x8007cbac`. The `jal` in [call-8007cb9c.md](call-8007cb9c.md) calls `ResetGraph` and returns here. This note does not state `ResetGraph`'s `v0`. The saved `ra` is `0x8007a6bc`. The caller `s1` is 13. The frame at `0x800251f8` stays open. Its saved `ra` stays `0x8007faec`.

`lw` at `0x8007cbac` loads `ra` from `sp+0x10`. `jr` at `0x8007cbb4` returns through `ra`. The delay slot adds `0x18` to `sp`. `ra` leaves as `0x8007a6bc`. Control goes to `0x8007a6bc`. That arrival is the next note. The caller return at `0x8007faec` is not traced.
