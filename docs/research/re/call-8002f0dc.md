# Function at 0x8002f0dc

Traced fact from the USA PS-X EXE. Re-check on a disc you own with `python3 tools/entry_disasm.py build/disc/SLUS_004.91 --start 0x8002f0dc`. The executable and the listing stay in `build/`. That tool stops at the first branch, the `bne` at `0x8002f10c`. Re-check the delay slot with `--start 0x8002f110`. That run's first instruction is the `ori`. The words after that instruction are not traced.

The start address is `0x8002f0dc`. The inventory size is 1000 bytes. This note has no boot caller. `a0`, `a1`, and `a2` are incoming arguments. Their values are not known. This note covers 14 instructions, including the delay slot, and stops at the unknown `bne`. The hard cap is 64 instructions. There is no `jal` or `jr` in this span.

`addu` at `0x8002f0dc` copies `a2` into `t7`. `lui` at `0x8002f0e0` sets `t6` to `0xc0000000`. `ori` at `0x8002f0e4` sets the low 16 bits, so `t6` becomes `0xc0000001`. `lui` at `0x8002f0e8` sets `t5` to `0x3fff0000`. `addiu` at `0x8002f0ec` sets `t3` to `t7` plus `0x38`. `lw` at `0x8002f0f0` loads the word at `0x0(a1)` into `v0`. `lw` at `0x8002f0f4` loads the word at `0x0(a0)` into `v1`. `lw` at `0x8002f0f8` loads the word at `0x14(t3)` into `t8`. That address is offset `0x4c` of `a2`. `subu` at `0x8002f0fc` subtracts `v1` from `v0`. `sra` at `0x8002f100` shifts that difference right by 8 into `t4`. The shift keeps the sign. `lb` at `0x8002f104` sign-extends the byte at offset `0x35` of `a2` into `v0`. `addiu` at `0x8002f108` sets `v1` to `0x1`. That add fills the byte load delay. It does not read `v0`. The three loaded words and the byte are not quoted.

`bne` at `0x8002f10c` compares `v0` with `v1` and targets `0x8002f128`. `v1` is `0x1`. The byte is not known. This note does not guess the taken side. The delay slot at `0x8002f110` is `ori t5, t5, 0xffff`. It sets `t5` to `0x3fffffff`. The delay slot runs on both sides. The branch target and the fall-through at `0x8002f114` are not traced.

This block writes `t3`, `t4`, `t5`, `t6`, `t7`, `t8`, `v0`, and `v1`. It reads `a0`, `a1`, `a2`, the words at `0x0(a0)` and `0x0(a1)`, the word at offset `0x4c` of `a2`, and the byte at offset `0x35` of `a2`. It does not read `a3`, `sp`, or `ra`. It does not write `a0`, `a1`, `a2`, `a3`, `sp`, or `ra`. `t7` leaves as `a2`. `t3` leaves as `a2` plus `0x38`. `t6` leaves as `0xc0000001`. `t5` leaves as `0x3fffffff`. `t4` leaves as the shifted difference. `t8` leaves as the word at offset `0x4c`. `v0` leaves as the sign-extended byte at offset `0x35`. `v1` leaves as `0x1`. `sp` and `ra` stay as they arrived.

The words at `0x8002f114` and `0x8002f128` are not traced. Both addresses are inside this function and inside the text image, `0x80010000` through `0x800c57ff`. This note does not close the gap in `components/exe/load.cpp`.

## Our code

No source file holds this prefix. The branch stays outside the tree. No ledger row is added.
