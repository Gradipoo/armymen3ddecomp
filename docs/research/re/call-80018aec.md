# Function at 0x80018aec

Traced fact from the USA PS-X EXE. Re-check on a disc you own with `python3 tools/entry_disasm.py build/disc/SLUS_004.91 --start 0x80018aec`. The executable and the listing stay in `build/`. That tool stops at `jr ra`. Re-check the delay slot with `--start 0x80018b40`. That run's first instruction is the `sh`. The words after that instruction are not traced.

The start address is `0x80018aec`. The inventory size is 88 bytes. This note has no boot caller. `a0` and `a1` are the incoming arguments. Their values are not known. The arriving `ra` is not known. This note covers 22 instructions, including the delay slot, and ends at `jr ra`. The hard cap is 64 instructions. There is no branch, `jal`, or `jalr`.

`sll` at `0x80018aec` shifts `a1` left by 1. `addu` at `0x80018af0` adds `a1` to that. `sll` at `0x80018af4` shifts the sum left by 3. That is the bit pattern of `a1` times 24. `lui` at `0x80018af8` sets `v0` to `0x800a0000`. `addiu` at `0x80018afc` adds `-0x16b8`, so `v0` becomes `0x8009e948`. `addu` at `0x80018b00` adds the scaled `a1` to that base and writes `v1`. `v1` is `0x8009e948` plus `a1` times 24. This note does not quote the bytes at that address.

`sh` at `0x80018b04` stores the low 16 bits of `a1` at offset `0xc` of `a0`. `lw` at `0x80018b08` loads the word at offset `0` of the row into `v0`. The `nop` at `0x80018b0c` fills the load delay. `sw` at `0x80018b10` stores that word at offset `0x8` of `a0`. `lhu` at `0x80018b14` loads the halfword at offset `0x4` of the row. The `nop` at `0x80018b18` fills the load delay. `sh` at `0x80018b1c` stores it at offset `0xe` of `a0`. `lhu` at `0x80018b20` loads the halfword at offset `0x8` of the row. The `nop` at `0x80018b24` fills the load delay. `sh` at `0x80018b28` stores it at offset `0x14` of `a0`. `lhu` at `0x80018b2c` loads the halfword at offset `0xc` of the row. The `nop` at `0x80018b30` fills the load delay. `sh` at `0x80018b34` stores it at offset `0x12` of `a0`. `lhu` at `0x80018b38` loads the halfword at offset `0x10` of the row into `v0`.

`jr` at `0x80018b3c` returns through the arriving `ra`. The `jr` does not read `v0`, so it fills that load delay. The delay slot at `0x80018b40` stores the loaded halfword at offset `0x10` of `a0`.

This block writes `v0`, `v1`, the halfword at offset `0xc`, the word at offset `0x8`, and the halfwords at offsets `0xe`, `0x10`, `0x12`, and `0x14`. It reads `a0`, `a1`, and that table row. It does not read `ra` or `sp`. It does not write `a0`, `a1`, `ra`, or `sp`. `a0` and `a1` stay as they arrived. `v1` leaves as `0x8009e948` plus `a1` times 24. `v0` leaves as the zero-extended halfword from offset `0x10` of that row. This note does not quote it. `ra` stays the arriving value.

After the delay slot, control goes to the arriving `ra`. The next address is that `ra`. The words at `0x80018b44` are not traced. `0x8009e948` and `0x80018b44` are inside the text image, `0x80010000` through `0x800c57ff`. This block does not load the word at `0x80018b44`. This note does not close the gap in `components/exe/load.cpp`.

## Our code

No source file is added for this function. The table bytes are not quoted. No ledger row is added.
