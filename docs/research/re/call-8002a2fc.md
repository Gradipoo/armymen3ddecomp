# Function at 0x8002a2fc

Traced fact from the USA PS-X EXE. Re-check on a disc you own with `python3 tools/entry_disasm.py build/disc/SLUS_004.91 --start 0x8002a2fc`. The executable and the listing stay in `build/`. That tool stops at the first branch, the `beq` at `0x8002a308`. Re-check the delay slot with `--start 0x8002a30c`. That run's first instruction is the `addiu`. The words after that instruction are not traced.

The start address is `0x8002a2fc`. The inventory size is 180 bytes. This note has no boot caller. This note covers 5 instructions, including the delay slot, and stops at the unknown `beq`. The hard cap is 64 instructions. There is no `jal` or `jr` in this span.

`lui` at `0x8002a2fc` sets `t0` to `0x800d0000`. `lw` at `0x8002a300` loads the word at `0x5f60(t0)` into `v1`. That address is `0x800d5f60`. `addiu` at `0x8002a304` sets `v0` to `0x4af`. That add fills the load delay. It does not read `v1`.

`beq` at `0x8002a308` compares `v1` with `v0` and targets `0x8002a3a8`. `v0` is still `0x4af` for that compare. The delay slot at `0x8002a30c` is `addiu v0, v1, 0x1`. It sets `v0` to the loaded word plus 1. The delay slot runs on both sides. The word at `0x800d5f60` is not known. This note does not load that word from the executable file. This note does not guess the taken side. The branch target and the fall-through at `0x8002a310` are not traced.

This block writes `t0`, `v0`, and `v1`. It reads the word at `0x800d5f60`. It does not read `a0`, `a1`, `a2`, `a3`, `sp`, or `ra`. It does not write `a0`, `a1`, `a2`, `a3`, `sp`, or `ra`. `t0` leaves as `0x800d0000`. `v1` leaves as the word at `0x800d5f60`. `v0` leaves as that word plus 1. `sp` and `ra` stay as they arrived. `0x800d5f60` sits past the text image, `0x80010000` through `0x800c57ff`, and below main RAM top `0x80200000`.

The words at `0x8002a310` and `0x8002a3a8` are not traced. Both addresses are inside this function and inside the text image. This note does not close the gap in `components/exe/load.cpp`.

## Our code

No source file holds this prefix. The branch stays outside the tree. No ledger row is added.
