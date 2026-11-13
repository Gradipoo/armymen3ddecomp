# Function at 0x8001ccbc

Traced fact from the USA PS-X EXE. Re-check on a disc you own with `python3 tools/entry_disasm.py build/disc/SLUS_004.91 --start 0x8001ccbc`. The executable and the listing stay in `build/`. That tool stops at `jr ra`. Re-check the delay slot with `--start 0x8001cce8`. That run's first instruction is the `sw`. The words after that instruction are not traced.

The start address is `0x8001ccbc`. The inventory size is 48 bytes. This note has no boot caller. The incoming `a0` is the argument this function reads. Its value is not known. The arriving `ra` is not known. This note covers 12 instructions, including the delay slot, and ends at `jr ra`. The hard cap is 64 instructions. There is no `jal` or `jalr`, so there is no named SDK or BIOS call. There is no branch.

`lui` at `0x8001ccbc` sets `v1` to `0x800a0000`. `lw` at `0x8001ccc0` loads the word at `0(a0)` into `v0`. `addiu` at `0x8001ccc4` adds `-0x7e0` to `v1`, so `v1` is `0x8009f820`. That add fills the load delay. `sw` at `0x8001ccc8` stores that loaded word at `0x8(v1)`. The address is `0x8009f828`. `lw` at `0x8001cccc` loads the word at `0x4(a0)` into `v0`. The `nop` at `0x8001ccd0` fills the load delay. `sw` at `0x8001ccd4` stores that word at `0x1c(v1)`. The address is `0x8009f83c`. `lw` at `0x8001ccd8` loads the word at `0x8(a0)` into `a1`. `lui` at `0x8001ccdc` sets `v0` to `0x800a0000`. That instruction fills the load delay. It does not read `a1`. `sw` at `0x8001cce0` stores `a0` at `-0x1510(v0)`. The address is `0x8009eaf0`.

`jr` at `0x8001cce4` returns through the arriving `ra`. The delay slot at `0x8001cce8` stores `a1` at `0x20(v1)`. The address is `0x8009f840`. `a1` is the word from offset `0x8`. The jump does not read `a1` or `v1`. The three loaded words are not quoted. This note does not read the old words at `0x8009f828`, `0x8009f83c`, `0x8009f840`, or `0x8009eaf0` from the executable file.

This block writes `v1`, `v0`, `a1`, and those four stored words. It reads `a0`, the arriving `ra`, and the words at offsets `0`, `0x4`, and `0x8`. It does not read the arriving `a1`, `a2`, or `a3`. It does not write `a0`, `ra`, or `sp`. `a0` stays the incoming pointer. `a1` leaves as the word at offset `0x8`. `v0` leaves as `0x800a0000`. `v1` leaves as `0x8009f820`. `ra` stays the arriving value. `sp` stays the arrival value.

After the delay slot, control goes to that arriving `ra`. The next address is that `ra`. The words at `0x8001ccec` are not traced. `0x8001ccec` is inside the text image, `0x80010000` through `0x800c57ff`. `0x8009f820` and `0x8009eaf0` are inside that same image. This note does not close the gap in `components/exe/load.cpp`.

## Our code

No source file is added for this function. No ledger row is added.
