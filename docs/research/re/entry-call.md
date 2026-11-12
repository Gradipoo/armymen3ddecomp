# Call from the entry

Traced fact from the USA PS-X EXE. Re-check on a disc you own with `python3 tools/entry_disasm.py build/disc/SLUS_004.91 --start 0x8007faf8`. The executable and the listing stay in `build/`.

The start address is `0x8007faf8`. The tool followed 2 instructions and stopped at the first branch. The hard cap is 64 instructions. This block ended before the cap.

`sltu` at `0x8007faf8` sets `t0` to 1 when `a0` is less than `a1` as an unsigned compare, and to 0 otherwise. `beq` at `0x8007fafc` branches to `0x8007fb14` when `t0` is 0. When `t0` is 1, the branch is not taken. The delay slot at `0x8007fb00` is `addi a1, a1, -0x4`, so `a1` drops by 4 on both paths. The fall-through address is `0x8007fb04`.

The `jal` at `0x8007fa24` reaches this block with `a0` equal to `0x1f800000` and `a1` equal to `0x1f800400`. Its delay slot is `nop`, so those registers are unchanged on entry. `0x1f800000` is less than `0x1f800400`, so `t0` is 1 and the branch is not taken. After the delay slot, that call continues at `0x8007fb04` with `a1` equal to `0x1f8003fc`.

The body past this block is not traced. This note does not close the gap in `components/exe/load.cpp`.
