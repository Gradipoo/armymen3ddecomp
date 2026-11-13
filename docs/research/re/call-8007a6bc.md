# Block at 0x8007a6bc

Traced fact from the USA PS-X EXE. Re-check on a disc you own with `python3 tools/entry_disasm.py build/disc/SLUS_004.91 --start 0x8007a6bc`. The executable and the listing stay in `build/`.

The start address is `0x8007a6bc`. The `jr` in [call-80059c08.md](call-80059c08.md) returns here. That `jr` at `0x80059c28` returns through `ra`. Its delay slot at `0x80059c2c` is `addiu sp, sp, 0x18`, so the frame opened at `0x80059bc8` is closed. The countdown in [call-80059bec.md](call-80059bec.md) left `v0` at `-0x1`. The `jr` and that `addiu` leave `v0` alone. `lw` at `0x80059c10` writes the word at `0x800d845c` into `v0`, and `ori` at `0x80059c18` ORs `0x10` into `v0`. The fill stored 0 at that word, so `v0` on return is `0x10`. This note does not read `0x800d8458` from the executable. On arrival `s0` is `0x80010000`, restored by the `lw` at `0x80059c24`. `s1` is `0x2`. That callee does not save `s1`. `s2` is `0x8001007c`, restored by the `lw` at `0x8007a614` in [call-8007a604.md](call-8007a604.md). The traced blocks after that restore do not write `s2`. `a0` is `0x800d89b4`, `a1` is 0, `a2` is 0, `t0` is 0, and `t1` is `0x4`. `ra` is `0x8007a6bc`. The caller is the function at `0x8007a628`, on the path that started at `0x8007a65c`. That frame is still open. The caller's `ra`, `0x800252ac`, stays in that frame. Which path reached the `jal` at `0x8002525c` is still unknown. The tool followed 3 instructions and stopped at the first branch. The hard cap is 64 instructions. This block ended before the cap. The branch goes backward to `0x8007a660`, so this block is a loop. It does not return to `0x8007a698`. The delay slot is the next word, at `0x8007a6c8`. Re-check it with `--start 0x8007a6c8`. That run's first instruction is the `addu`. The words after that instruction are not traced.

`addiu` at `0x8007a6bc` is `addiu s0, s0, 0x4`. It adds 4 to `s0`, so `s0` becomes `0x80010004`. `s0` is the cursor.

`sltu` at `0x8007a6c0` is `sltu v0, s0, s2`. It sets `v0` to 1 when `s0` is below `s2` as unsigned values, and to 0 otherwise. `s2` is the unsigned upper bound, `0x8001007c`. `0x80010004` is below `0x8001007c`, so `v0` is 1. The arriving `v0` is not read.

`bne` at `0x8007a6c4` is `bne v0, zero, 0x8007a660`. It branches to `0x8007a660` when `v0` is not 0. `v0` is 1, so the branch is taken. When `v0` is 0, the branch is not taken. The delay slot at `0x8007a6c8` is `addu a0, s0, zero`. It copies the new `s0` into `a0` on both outcomes, so `a0` becomes `0x80010004`. The fall-through address is `0x8007a6cc`.

The taken path goes back to `0x8007a660` while the new `s0` is below `s2`. [call-8007a65c.md](call-8007a65c.md) names the word at `0x8007a660` as `jal 0x8007a540`. This note does not trace that body and does not unroll the loop. The branch target is `0x8007a660`. The loop does not return to `0x8007a698`.

These bytes do not read or write `s1`. `s1` stays `0x2`.

This block writes `s0` and `v0`. The delay slot writes `a0`. It reads the arriving `s0`, the new `s0`, and `s2`, then reads `v0`. `a1` stays 0, `a2` stays 0, `t0` stays 0, and `t1` stays `0x4`. `ra` stays `0x8007a6bc`. It does not write `sp`. The stack slots saved at `0x8007a628` stay as they were. The stack slots saved at `0x800251f8` stay as they were. The word at `0x8007f9a8` is not read.

After the delay slot, control goes to `0x8007a660` when `v0` is not 0, and to `0x8007a6cc` when `v0` is 0. This boot takes `0x8007a660`. The body at `0x8007a660` is not traced. The body at `0x8007a6cc` is not traced. The words at `0x800252ac` are not traced. The caller return at `0x8007faec` is not traced. This note does not close the gap in `components/exe/load.cpp`.
