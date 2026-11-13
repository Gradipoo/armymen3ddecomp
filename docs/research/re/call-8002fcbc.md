# Function at 0x8002fcbc

Traced fact from the USA PS-X EXE. Re-check on a disc you own with `python3 tools/entry_disasm.py build/disc/SLUS_004.91 --start 0x8002fcbc`. The executable and the listing stay in `build/`. That tool stops at the first branch, the `bgez` at `0x8002fce8`. Re-check the delay slot with `--start 0x8002fcec`. That run's first instruction is the `addu`. The words after that instruction are not traced.

The start address is `0x8002fcbc`. The inventory size is 400 bytes. This note has no boot caller. `a0` and `a1` are the incoming arguments. Their values are not known. The arriving `ra` is not known. This note covers 13 instructions, including the delay slot, and stops at the unknown `bgez`. The hard cap is 64 instructions. There is no `jal` or `jalr` in this span. There is no `jr`.

`addiu` at `0x8002fcbc` subtracts `0x30` from `sp`. `sw` at `0x8002fcc0` saves the arriving `s1` at `0x14(sp)`. `addu` at `0x8002fcc4` copies `a0` into `s1`. `sw` at `0x8002fcc8` saves the arriving `ra` at `0x28(sp)`. `sw` at `0x8002fccc` through `0x8002fcdc` save `s5`, `s4`, `s3`, `s2`, and `s0` at `0x24(sp)`, `0x20(sp)`, `0x1c(sp)`, `0x18(sp)`, and `0x10(sp)`. `lw` at `0x8002fce0` loads the word at offset `0x18` of `s1` into `v0`. `s1` is the first argument. The `nop` at `0x8002fce4` fills that load delay. This block does not read that word from the executable file.

`bgez` at `0x8002fce8` tests `v0`. That word is not known, so this note does not choose a side. The delay slot at `0x8002fcec` copies `a1` into `s5`. The copy runs on both outcomes. When the word is not negative, the branch goes to `0x8002fcf4`. The words there are not traced. When the word is negative, the next instruction is `0x8002fcf0`. The words there are not traced.

This block writes `sp`, `s1`, `s5`, `v0`, and the seven saved slots. It reads `sp`, the arriving `s0`, `s1`, `s2`, `s3`, `s4`, `s5`, and `ra`, `a0`, `a1`, and the word at offset `0x18`. It does not read `a2` or `a3`. It does not write the first argument. It does not write `a0`, `a1`, or `ra`. The slot at `0x10(sp)` holds the old `s0`. The slot at `0x14(sp)` holds the old `s1`. The slot at `0x18(sp)` holds the old `s2`. The slot at `0x1c(sp)` holds the old `s3`. The slot at `0x20(sp)` holds the old `s4`. The slot at `0x24(sp)` holds the old `s5`. The slot at `0x28(sp)` holds the arriving `ra`. `s1` leaves as the first argument. `s5` leaves as the second argument. `a0` stays the first argument. `a1` stays the second argument. `v0` leaves as the word at offset `0x18`. `ra` stays the arriving value. `sp` is `0x30` below the arrival value.

After the delay slot, the taken side is `0x8002fcf4` and the other side is `0x8002fcf0`. Both addresses are inside the text image, `0x80010000` through `0x800c57ff`. This prefix is not the whole function. This note does not close the gap in `components/exe/load.cpp`.

## Our code

No source file is added for this prefix. The load and both branch sides stay out of the tree. No ledger row is added.
