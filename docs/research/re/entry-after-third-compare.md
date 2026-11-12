# After the third byte compare

Traced fact from the USA PS-X EXE. Re-check on a disc you own with `python3 tools/entry_disasm.py build/disc/SLUS_004.91 --start 0x8007fad4`. The executable and the listing stay in `build/`.

The start address is `0x8007fad4`. The `jal` at `0x8007facc` set `ra` to this address. That call is in [entry-after-second-compare.md](entry-after-second-compare.md). The tool followed 5 instructions and stopped at the first jump. The hard cap is 64 instructions. This block ended before the cap.

`or` at `0x8007fad4` writes `t0` as `t0` OR `v0`. `t0` still holds the OR of the earlier compare results, and `v0` is the result of the call that returned here. Which values this boot has is unknown, because the BIOS ROM is not in this tree. This block does not branch on `t0` or `v0`.

`lui` at `0x8007fad8` loads `0x80080000` into `a0`. `addiu` at `0x8007fadc` adds `-0x658`, so `a0` is `0x8007f9a8`. `sw` at `0x8007fae0` stores `t0` at `0x8007f9a8`.

`jal` at `0x8007fae4` targets `0x800251f8` and sets `ra` to `0x8007faec`. The delay slot at `0x8007fae8` is `nop`. Re-check it with `--start 0x8007fae8`. After the delay slot, control goes to `0x800251f8`. The `or` result does not change that target. The only branch or jump in this block is that `jal`.

This block writes `t0`, `a0`, the word at `0x8007f9a8`, and `ra`. It reads `v0` and does not write it. `0x8007f9a8` sits `0x50` bytes before the entry at `0x8007f9f8`. The callee at `0x800251f8` is not traced. The body at `0x8007faec` is not traced. This note does not close the gap in `components/exe/load.cpp`.
