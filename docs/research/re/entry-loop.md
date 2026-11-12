# Loop after the entry call

Traced fact from the USA PS-X EXE. Re-check on a disc you own with `python3 tools/entry_disasm.py build/disc/SLUS_004.91 --start 0x8007fb04`. The executable and the listing stay in `build/`.

The start address is `0x8007fb04`. The tool followed 3 instructions and stopped at the first branch. The hard cap is 64 instructions. This block ended before the cap. The branch target is `0x8007fb04`, so the three instructions are a loop. The delay slot is the next word, at `0x8007fb10`. Re-check it with `--start 0x8007fb10`. That run stops at the jump at `0x8007fb14`.

`sw` at `0x8007fb04` writes the word in `a2` to the address in `a0`. `sltu` at `0x8007fb08` sets `t0` to 1 when `a0` is less than `a1` as an unsigned compare, and to 0 otherwise. `bne` at `0x8007fb0c` branches to `0x8007fb04` when `t0` is not 0. The delay slot at `0x8007fb10` is `addi a0, a0, 0x4`, so `a0` rises by 4 whether the branch is taken or not. The compare uses `a0` from before that add.

This call enters with `a0` equal to `0x1f800000` and `a1` equal to `0x1f8003fc`. `a2` is still `0x55555555` from the entry block: the instructions from `0x8007faf8` through `0x8007fb00` do not write `a2`. Each pass stores that word, then adds 4 to `a0`, and repeats while the old `a0` is below `a1`. The stores cover every word from `0x1f800000` through `0x1f8003fc`. That is the scratchpad, `0x1f800000` through `0x1f8003ff`. The loop writes that range. The compare and the step use registers.

When `a0` equals `a1`, `t0` is 0 and the branch is not taken. The delay slot still adds 4, so `a0` leaves as `0x1f800400`. Execution continues at `0x8007fb14`.

`jr` at `0x8007fb14` returns through `ra`. Its delay slot at `0x8007fb18` is `nop`. The `jal` at `0x8007fa24` set `ra` to `0x8007fa2c`, so control goes there. This call reaches `0x8007fb14` only after the loop. The `beq` at `0x8007fafc` names that same address and is not taken on this call.

The caller body at `0x8007fa2c` is in [entry-return.md](entry-return.md). This note does not close the gap in `components/exe/load.cpp`.
