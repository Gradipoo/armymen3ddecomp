# Function at 0x80030bcc

Traced fact from the USA PS-X EXE. Re-check on a disc you own with `python3 tools/entry_disasm.py build/disc/SLUS_004.91 --start 0x80030bcc`. The executable and the listing stay in `build/`. That tool stops at the first jump, the `jal` at `0x80030bf0`. Re-check the delay slot with `--start 0x80030bf4`. Re-check the return with `--start 0x80030bf8`. That run stops at `jr`. Re-check its delay slot with `--start 0x80030c40`. That run's first instruction is the `addiu`.

The start address is `0x80030bcc`. The inventory size is 120 bytes. This note has no boot caller. `a0`, `a1`, `a2`, and `a3` are the incoming arguments. Their values are not known. This note covers 30 instructions, including delay slots, and ends at `jr ra`. The hard cap is 64 instructions. The only call is named.

`addiu` at `0x80030bcc` subtracts `0x38` from `sp`. `sw` at `0x80030bd0` saves the arriving `s0` at `0x30(sp)`. `addu` at `0x80030bd4` copies `a0` into `s0`. `addiu` at `0x80030bd8` adds `0x4` to `s0` and writes `a0`. `sw` at `0x80030bdc` stores the incoming `a1` at `0x10(sp)`. `addiu` at `0x80030be0` sets `a1` to `sp` plus `0x10`. `sw` at `0x80030be4` stores the incoming `a2` at `0x14(sp)`. `addiu` at `0x80030be8` sets `a2` to `sp` plus `0x20`. `sw` at `0x80030bec` saves the arriving `ra` at `0x34(sp)`.

`jal` at `0x80030bf0` targets `0x8008b98c` and sets `ra` to `0x80030bf8`. The delay slot at `0x80030bf4` is `sw a3, 0x18(sp)`. It stores the incoming `a3` at `0x18(sp)`. It does not write the `a3` register. `a0` is the first argument plus `0x4`. `a1` points at the three stored words. `a2` points at `0x20(sp)`. `python3 tools/sdk_match.py build/disc/SLUS_004.91` names `0x8008b98c` `ApplyMatrixLV`. The BIOS table in [bios.md](bios.md) does not name it. This note does not enter that body. This note does not see that body write `s0`, or the words at `0x20(sp)`, `0x24(sp)`, and `0x28(sp)`. `v0` on return is not read.

`lw` at `0x80030bf8` loads the word at offset `0x18` into `v0`. `lw` at `0x80030bfc` loads the word at `0x20(sp)` into `v1` and fills the first load delay. The `nop` at `0x80030c00` fills the second load delay. `addu` at `0x80030c04` adds them. `sw` at `0x80030c08` stores the sum at offset `0x18`. `lw` at `0x80030c0c` loads the word at offset `0x1c` into `v0`. `lw` at `0x80030c10` loads the word at `0x24(sp)` into `v1` and fills the first load delay. The `nop` at `0x80030c14` fills the second load delay. `addu` at `0x80030c18` adds them. `sw` at `0x80030c1c` stores the sum at offset `0x1c`. `lw` at `0x80030c20` loads the word at offset `0x20` into `v0`. `lw` at `0x80030c24` loads the word at `0x28(sp)` into `v1` and fills the first load delay. The `nop` at `0x80030c28` fills the second load delay. `addu` at `0x80030c2c` adds them. `sw` at `0x80030c30` stores the sum at offset `0x20`.

`lw` at `0x80030c34` restores `ra` from `0x34(sp)`. `lw` at `0x80030c38` restores `s0` from `0x30(sp)`. `jr` at `0x80030c3c` returns through that `ra`. The delay slot at `0x80030c40` adds `0x38` to `sp`. The restored `ra` is the caller of this function. That address is not known.

This block writes `sp`, the two saved slots, `s0`, `a0`, `a1`, `a2`, `ra`, the three argument words on the stack, and the words at offsets `0x18`, `0x1c`, and `0x20`. It reads `sp`, the arriving `s0` and `ra`, the four incoming arguments, those three object words, and the three words at `0x20(sp)`, `0x24(sp)`, and `0x28(sp)`. It does not write the `a3` register. `v0` leaves as the sum stored at offset `0x20`. `s0` leaves as the old `s0`. `ra` leaves as the caller of this function. `sp` is restored.

After the delay slot, control goes to that restored `ra`. The body at `0x8008b98c` is not traced. `0x8008b98c` and `0x80030bf8` are inside the text image, `0x80010000` through `0x800c57ff`. This note does not close the gap in `components/exe/load.cpp`.

## Our code

No file under `components/exe` implements `0x80030bcc`. The `ApplyMatrixLV` call stays open. No ledger row is added.
