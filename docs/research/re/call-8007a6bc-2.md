# Second arrival at 0x8007a6bc

Traced fact from the USA PS-X EXE. Re-check on a disc you own with `python3 tools/entry_disasm.py build/disc/SLUS_004.91 --start 0x8007a6bc`. The executable and the listing stay in `build/`.

The start address is `0x8007a6bc`. The `jr` in [call-800621bc.md](call-800621bc.md) returns here. That note is the first return to this address. This arrival is the next one. On arrival `s0` is `0x80010004`, `s1` is 3, and `s2` is `0x8001007c`. `ra` is `0x8007a6bc`. The frame at `0x8007a628` stays open. Its saved `ra` stays `0x800252ac`. The frame at `0x800251f8` stays open. Its saved `ra` stays `0x8007faec`. The stores in [call-8007a688.md](call-8007a688.md) still hold: the word at `0x80010004` is `0x800b5948` and the word at `0x8001000c` is `0x800b3b68`.

`addiu` at `0x8007a6bc` adds 4 to `s0`, so `s0` becomes `0x80010008`. `sltu` at `0x8007a6c0` compares that with `s2`. `0x80010008` is below `0x8001007c`, so `v0` is 1. `bne` at `0x8007a6c4` is taken to `0x8007a660`. The delay slot copies `s0` into `a0`. `a0` becomes `0x80010008`.

`jal` at `0x8007a660` targets `0x8007a540`. `ra` becomes `0x8007a668`. The delay slot copies `s2` into `a1`, so `a1` is `0x8001007c`. [call-8007a540.md](call-8007a540.md) and [call-8007a540-2.md](call-8007a540-2.md) are other entries. This note does not enter the body.

`s1` stays 3. The next note is this entry of `0x8007a540`. The caller return at `0x8007faec` is not traced.
