# Return after the scratchpad fill

Traced fact from the USA PS-X EXE. Re-check on a disc you own with `python3 tools/entry_disasm.py build/disc/SLUS_004.91 --start 0x8007fa2c`. The executable and the listing stay in `build/`.

The start address is `0x8007fa2c`. The `jr` at `0x8007fb14` returns through `ra`, and the `jal` at `0x8007fa24` set `ra` to this address. The tool followed 7 instructions and stopped at the first jump. The hard cap is 64 instructions. This block ended before the cap.

`lui` at `0x8007fa2c` loads `0x80010000` into `a0`. `addiu` at `0x8007fa30` adds `0x7c`, so `a0` is `0x8001007c`. `lui` at `0x8007fa34` loads `0x80010000` into `a1`. `addiu` at `0x8007fa38` adds `0xc7c`, so `a1` is `0x80010c7c`. `lui` at `0x8007fa3c` loads `0x55550000` into `a2`. `ori` at `0x8007fa40` ORs in `0x5555`, so `a2` is `0x55555555`.

`jal` at `0x8007fa44` targets `0x8007faf8` and sets `ra` to `0x8007fa4c`. The delay slot at `0x8007fa48` is `nop`. Re-check it with `--start 0x8007fa48`. That run stops at the jump at `0x8007fa60`. After the delay slot, control goes to `0x8007faf8`.

This block writes `a0`, `a1`, `a2`, and `ra`. The callee is the block in [entry-call.md](entry-call.md). This call fills `0x8001007c` through the last word before `0x80010c7c` with `0x55555555`, using the function already described in [entry-loop.md](entry-loop.md). The return continues in [entry-after-fill.md](entry-after-fill.md). This note does not close the gap in `components/exe/load.cpp`.
