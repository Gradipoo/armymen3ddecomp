# Function at 0x8002ba0c

Traced fact from the USA PS-X EXE. Re-check on a disc you own with `python3 tools/entry_disasm.py build/disc/SLUS_004.91 --start 0x8002ba0c`. The executable and the listing stay in `build/`. That tool stops at the first branch, the `beq` at `0x8002ba1c`. Re-check the delay slot with `--start 0x8002ba20`. That run's first instruction is the `addu`. The words after that instruction are not traced.

The start address is `0x8002ba0c`. The inventory size is 220 bytes. This note has no boot caller. The incoming `a1` is a pointer. Its value is not known. This prefix does not read `a0`. The arriving `ra` is not known. This note covers 6 instructions, including the delay slot, and stops at the unknown `beq`. The hard cap is 64 instructions. There is no `jal` or `jalr` in this span, so there is no named SDK or BIOS call. There is no `jr` in this span.

`addu` at `0x8002ba0c` sets `a2` to 0. `addu` at `0x8002ba10` copies `a2` into `v1`, so `v1` is 0. `lw` at `0x8002ba14` loads the word at `0(a1)` into `a3`. That word is not quoted. The `nop` at `0x8002ba18` fills the load delay.

`beq` at `0x8002ba1c` compares `a3` with zero. `a3` is not known, so the branch is not known. The delay slot at `0x8002ba20` copies `a2` into `v0`, so `v0` is 0 on both outcomes. When `a3` is zero, the branch goes to `0x8002ba30`. When `a3` is not zero, control falls through to `0x8002ba24`. This note does not follow either side.

This block writes `a2`, `a3`, `v0`, and `v1`. It reads `a1` and the word at offset `0`. It does not read `a0`, `a2`, `a3`, or `ra`. It does not write `a0`, `a1`, `ra`, or `sp`. `a0` stays the incoming first argument. `a1` stays the second pointer. `a2` leaves as 0. `a3` leaves as the loaded word. `v0` leaves as 0. `v1` leaves as 0. `ra` stays the arriving value. `sp` stays the arrival value.

The words at `0x8002ba24` are not traced. The words at `0x8002ba30` are not traced. Both addresses are inside the text image, `0x80010000` through `0x800c57ff`. This prefix is not the whole function. This note does not close the gap in `components/exe/load.cpp`.

## Our code

No source file is added for this function. The two sides of the `beq` stay outside this note. No ledger row is added.
