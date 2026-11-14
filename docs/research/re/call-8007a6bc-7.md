# Seventh arrival at 0x8007a6bc

Traced fact from the USA PS-X EXE. Re-check on a disc you own with `python3 tools/entry_disasm.py build/disc/SLUS_004.91 --start 0x8007a6bc`. The executable and the listing stay in `build/`.

The start address is `0x8007a6bc`. The `jr` in [call-80076500.md](call-80076500.md) returns here. On arrival `s0` is `0x80010018`, `s1` is 8, and `s2` is `0x8001007c`. The frame at `0x800251f8` stays open. Its saved `ra` stays `0x8007faec`. The stores in [call-8007a668-7.md](call-8007a668-7.md) are still live.

`addiu` at `0x8007a6bc` makes `s0` `0x8001001c`. That value is below `s2`, so `sltu` sets `v0` to 1 and `bne` at `0x8007a6c4` is taken. The delay slot copies `s0` into `a0`. `a0` is `0x8001001c`.

`jal` at `0x8007a660` targets `0x8007a540`. `ra` becomes `0x8007a668`. The delay slot copies `s2` into `a1`, so `a1` is `0x8001007c`. `s1` stays 8. This note does not enter the body. The next note is this entry. The caller return at `0x8007faec` is not traced.
