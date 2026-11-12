# Entry

Traced fact from the USA PS-X EXE. Re-check on a disc you own with `python3 tools/entry_disasm.py build/disc/SLUS_004.91`. The executable and the listing stay in `build/`.

The entry address is `0x8007f9f8`. The tool followed 12 instructions from that address and stopped at the first jump. The hard cap is 64 instructions. This block ended before the cap.

The block sets `sp` and `fp`, then `gp`, then `a0`, `a1`, and `a2`, then calls `0x8007faf8`.

`lui` at `0x8007f9f8` loads `0x80010000` into `a0`. `addiu` at `0x8007f9fc` adds `0xc64`, so `a0` is `0x80010c64`. `addu` at `0x8007fa00` copies that value to `sp`. `addu` at `0x8007fa04` copies it to `fp`.

`lui` at `0x8007fa08` and `addiu` at `0x8007fa0c` set `gp` to `0x800c5424`.

Five instructions from `0x8007fa10` through `0x8007fa20` set the argument registers. `a0` becomes `0x1f800000`. `a1` becomes `0x1f800400`. `a2` becomes `0x55555555`.

`jal` at `0x8007fa24` targets `0x8007faf8` and sets `ra` to `0x8007fa2c`. The delay slot is the instruction at `0x8007fa28`. This note does not decode that word. After the delay slot, control goes to `0x8007faf8`.

The function body is not traced past this block. This note does not close the gap in `components/exe/load.cpp`.
