# Block at 0x8007c3dc

Traced fact from the USA PS-X EXE. Re-check on a disc you own with `python3 tools/entry_disasm.py build/disc/SLUS_004.91 --start 0x8007c3dc`. The executable and the listing stay in `build/`.

The start address is `0x8007c3dc`. The `jr` in [call-8007f920-17.md](call-8007f920-17.md) returns here. `s1` is `0x1010`. `s0` is `0x67fc0`. `s2` is `0x800e1920`. `s3` is `0x800e0000`. `v0` arrived as `0x800e1920` and is not read. The caller `s1` is 18. The frame at `0x800251f8` stays open. Its saved `ra` stays `0x8007faec`. The bytes from `0x800e1920` through `0x801498df` are 0 before these stores.

`sw` at `0x8007c3dc` stores `0x1010` at `0x800e1920`. `sw` at `0x8007c3e0` stores `0x1010` at `0x800e1924`. `sw` at `0x8007c3e4` stores `0x67fc0` at `0x800e1928`. The restores do not change those words. `jr` at `0x8007c3fc` returns through the saved `ra`. The delay slot adds `0x28` to `sp`. `ra` leaves as `0x8007a6bc`. Control goes to `0x8007a6bc`. That arrival is the next note. The caller return at `0x8007faec` is not traced.
