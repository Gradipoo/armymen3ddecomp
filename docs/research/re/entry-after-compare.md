# After the byte compare

Traced fact from the USA PS-X EXE. Re-check on a disc you own with `python3 tools/entry_disasm.py build/disc/SLUS_004.91 --start 0x8007fa9c`. The executable and the listing stay in `build/`.

The start address is `0x8007fa9c`. The `jr` at `0x8007fb3c` returns here. The `jal` at `0x8007fa94` set `ra` to this address. That return is in [entry-byte-compare.md](entry-byte-compare.md). The tool followed 6 instructions and stopped at the first jump. The hard cap is 64 instructions. This block ended before the cap.

`addu` at `0x8007fa9c` copies `v0` into `t0`. The return in that note leaves `v0` as 0 or as 1. Which value this boot has is unknown, because the BIOS ROM is not in this tree. The copy is the only use of `v0` here.

`lui` at `0x8007faa0` loads `0x80080000` into `a0`. `addiu` at `0x8007faa4` adds `-0x61e`, so `a0` is `0x8007f9e2`. `lui` at `0x8007faa8` loads `0x1fc00000` into `a1`. `ori` at `0x8007faac` ORs in `0x12c`, so `a1` is `0x1fc0012c`.

`jal` at `0x8007fab0` targets `0x8007fb1c` and sets `ra` to `0x8007fab8`. The delay slot at `0x8007fab4` is `nop`. Re-check it with `--start 0x8007fab4`. After the delay slot, control goes to `0x8007fb1c`. Either value of `v0` takes that same target.

This block writes `t0`, `a0`, `a1`, and `ra`. `0x8007f9e2` sits `0x16` bytes before the entry at `0x8007f9f8`. `a1` is `0x12c` bytes into the BIOS ROM. That ROM is not in this tree. The callee is the block in [entry-bios-call.md](entry-bios-call.md). Whether the new bytes match stays open. The body at `0x8007fab8` is not traced. This note does not close the gap in `components/exe/load.cpp`.
