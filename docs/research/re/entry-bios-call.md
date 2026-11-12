# Call with a BIOS address

Traced fact from the USA PS-X EXE. Re-check on a disc you own with `python3 tools/entry_disasm.py build/disc/SLUS_004.91 --start 0x8007fb1c`. The executable and the listing stay in `build/`.

The start address is `0x8007fb1c`. The `jal` at `0x8007fa94` set `ra` to `0x8007fa9c`. The tool followed 3 instructions and stopped at the first branch. The hard cap is 64 instructions. This block ended before the cap.

`lbu` at `0x8007fb1c` loads the unsigned byte at `a0` into `v0`. `lbu` at `0x8007fb20` loads the unsigned byte at `a1` into `v1`. `beq` at `0x8007fb24` branches to `0x8007fb3c` when `v0` is 0. When `v0` is not 0, the branch is not taken. The delay slot at `0x8007fb28` is `addiu a0, a0, 0x1`, so `a0` rises by 1 on both paths. Re-check it with `--start 0x8007fb28`. That run stops at the branch at `0x8007fb34`. The fall-through address is `0x8007fb2c`.

On entry, `a0` is `0x8007f9d8` and `a1` is `0x1fc00129`. The delay slot at `0x8007fa98` is `nop`, so those registers are unchanged. `0x8007f9d8` sits `0x20` bytes before the entry at `0x8007f9f8`. `0x1fc00000` is the start of the PlayStation BIOS ROM, so `a1` points `0x129` bytes into that ROM. This block uses `a0` and `a1` as byte addresses. The branch tests the byte from `a0`. The byte from `a1` stays in `v1`. The body past this branch is not traced. This note does not close the gap in `components/exe/load.cpp`.
