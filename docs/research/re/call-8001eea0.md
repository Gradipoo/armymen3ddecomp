# Function at 0x8001eea0

Traced fact from the USA PS-X EXE. Re-check on a disc you own with `python3 tools/entry_disasm.py build/disc/SLUS_004.91 --start 0x8001eea0`. The executable and the listing stay in `build/`. That tool stops at `jr ra`. Re-check the delay slot with `--start 0x8001eefc`. That run's first instruction is the `sb`. The words after that instruction are not traced.

The start address is `0x8001eea0`. The inventory size is 96 bytes. This note has no boot caller. The incoming `a0` is the first argument. Its value is not known. This note covers 24 instructions, including the delay slot, and ends at `jr ra`. The hard cap is 64 instructions. There is no `jal` or `jalr`, so there is no named SDK or BIOS call.

`addiu` at `0x8001eea0` writes 4 into `v0`. `addiu` at `0x8001eea4` writes 1 into `v1`. `sh` at `0x8001eea8` stores 4 at offset `0xac`. `addiu` at `0x8001eeac` writes `0x40` into `v0`. `sh` at `0x8001eeb0` stores `0x40` at offset `0xb6`. `sh` at `0x8001eeb4` stores `0x40` at offset `0xb8`. `addiu` at `0x8001eeb8` writes `0x80` into `v0`. `sb` at `0x8001eebc` stores `0x80` at offset `0xba`. The same byte is stored at offsets `0xbb`, `0xbc`, `0xbe`, `0xbf`, and `0xc0`. Offset `0xbd` is not written.

`addiu` at `0x8001eed4` writes `-1` into `v0`, so `v0` is `0xffffffff`. `sh` at `0x8001eed8` stores 1 at offset `0x9a`. `sh` at `0x8001eedc` stores 1 at offset `0xae`. `sh` at `0x8001eee0` stores 0 at offset `0xb2`. `sh` at `0x8001eee4` stores 0 at offset `0xb4`. `sw` at `0x8001eee8` stores 0 at offset `0x78`. `sw` at `0x8001eeec` stores 0 at offset `0x7c`. `sw` at `0x8001eef0` stores 0 at offset `0x80`. `sh` at `0x8001eef4` stores the low 16 bits of `v0` at offset `0x98`. Those bits are `0xffff`.

`jr` at `0x8001eef8` returns through the arriving `ra`. The delay slot at `0x8001eefc` stores 1 at offset `0x34`. The halfword stores and the word stores use `a0` before that byte store.

This block writes `v0`, `v1`, and those fields of the first argument. It reads `a0` and `ra`. It does not read `a1`, `a2`, or `a3`. It does not write `a0`, `sp`, or `ra`. `v0` leaves as `0xffffffff`. `v1` leaves as 1. `a0` stays the first argument. `ra` stays as it arrived. `sp` stays as it arrived.

After the delay slot, control goes to the arriving `ra`. The words at `0x8001ef00` are not traced. `0x8001ef00` is inside the text image, `0x80010000` through `0x800c57ff`. This note does not close the gap in `components/exe/load.cpp`.

## Our code

The traced function writes these constants into the first argument and returns `0xffffffff`. Offset `0xbd` stays unchanged. This note does not close the gap in `components/exe/load.cpp`.
