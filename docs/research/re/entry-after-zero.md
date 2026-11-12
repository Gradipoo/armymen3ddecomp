# After the zero fill

Traced fact from the USA PS-X EXE. Re-check on a disc you own with `python3 tools/entry_disasm.py build/disc/SLUS_004.91 --start 0x8007fa68`. The executable and the listing stay in `build/`.

The start address is `0x8007fa68`. The `jal` at `0x8007fa60` set `ra` to this address. The tool followed 6 instructions and stopped at the first jump. The hard cap is 64 instructions. This block ended before the cap.

`lui` at `0x8007fa68` loads `0x800e0000` into `a0`. `addiu` at `0x8007fa6c` adds `0x44e0`, so `a0` is `0x800e44e0`. `lui` at `0x8007fa70` loads `0x80200000` into `a1`. `lui` at `0x8007fa74` loads `0x55550000` into `a2`. `ori` at `0x8007fa78` ORs in `0x5555`, so `a2` is `0x55555555`.

`jal` at `0x8007fa7c` targets `0x8007faf8` and sets `ra` to `0x8007fa84`. The delay slot at `0x8007fa80` is `nop`. Re-check it with `--start 0x8007fa80`. That run stops at the jump at `0x8007fa94`. After the delay slot, control goes to `0x8007faf8`.

This block writes `a0`, `a1`, `a2`, and `ra`. The callee is the block in [entry-call.md](entry-call.md). This call fills `0x800e44e0` through the last word before `0x80200000` with `0x55555555`, using the function already described in [entry-loop.md](entry-loop.md). The body past this jump is not traced. This note does not close the gap in `components/exe/load.cpp`.
