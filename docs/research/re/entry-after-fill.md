# After the second fill

Traced fact from the USA PS-X EXE. Re-check on a disc you own with `python3 tools/entry_disasm.py build/disc/SLUS_004.91 --start 0x8007fa4c`. The executable and the listing stay in `build/`.

The start address is `0x8007fa4c`. The `jal` at `0x8007fa44` set `ra` to this address. The tool followed 6 instructions and stopped at the first jump. The hard cap is 64 instructions. This block ended before the cap.

`lui` at `0x8007fa4c` loads `0x800c0000` into `a0`. `addiu` at `0x8007fa50` adds `0x5458`, so `a0` is `0x800c5458`. `lui` at `0x8007fa54` loads `0x800e0000` into `a1`. `addiu` at `0x8007fa58` adds `0x44e0`, so `a1` is `0x800e44e0`. `addiu` at `0x8007fa5c` adds `0x0` to `zero`, so `a2` is 0.

`jal` at `0x8007fa60` targets `0x8007faf8` and sets `ra` to `0x8007fa68`. The delay slot at `0x8007fa64` is `nop`. Re-check it with `--start 0x8007fa64`. That run stops at the jump at `0x8007fa7c`. After the delay slot, control goes to `0x8007faf8`.

This block writes `a0`, `a1`, `a2`, and `ra`. The callee is the block in [entry-call.md](entry-call.md). The body past this jump is not traced. This note does not close the gap in `components/exe/load.cpp`.
