# Function at 0x80010fbc

Traced fact from the USA PS-X EXE. Re-check on a disc you own with `python3 tools/entry_disasm.py build/disc/SLUS_004.91 --start 0x80010fbc`. The executable and the listing stay in `build/`. That tool stops at the first jump, the `jal` at `0x80010fd4`. Re-check the delay slot with `--start 0x80010fd8`. That run's first instruction is the `sw`. The words after that instruction are not traced.

The start address is `0x80010fbc`. The inventory size is 72 bytes. This note has no boot caller. `a0` is the incoming argument. Its value is not known. The arriving `ra` is not known. This note covers 8 instructions, including the delay slot, and stops at the first unnamed `jal`. The hard cap is 64 instructions.

`addiu` at `0x80010fbc` subtracts `0x18` from `sp`. `sw` at `0x80010fc0` saves the arriving `s0` at `0x10(sp)`. `addu` at `0x80010fc4` then copies `a0` into `s0`. `lui` at `0x80010fc8` sets `v0` to `0x800c0000`. `addiu` at `0x80010fcc` adds `0x5c`, so `v0` becomes `0x800c005c`. `sw` at `0x80010fd0` saves the arriving `ra` at `0x14(sp)`.

`jal` at `0x80010fd4` targets `0x8002fb9c` and sets `ra` to `0x80010fdc`. The delay slot at `0x80010fd8` is `sw v0, 0x68(s0)`. It stores `0x800c005c` at offset `0x68` of the object. `a0` stays the object. The delay slot does not write `a0`, `a1`, `a2`, or `a3`. `python3 tools/sdk_match.py build/disc/SLUS_004.91` does not name `0x8002fb9c`. The BIOS table in [bios.md](bios.md) does not name it. This note does not enter that body.

This block writes `sp`, the saved slots, `s0`, `v0`, and `ra`, and the word at `0x68(s0)`. It reads `sp`, the arriving `s0`, the arriving `ra`, and `a0`. It does not read `a1`, `a2`, `a3`, or the arriving `v0`. It does not write `a0`, `a1`, `a2`, or `a3`. `s0` leaves as the object. `v0` leaves as `0x800c005c`. `ra` leaves as `0x80010fdc`. The slot at `0x10(sp)` holds the old `s0`. The slot at `0x14(sp)` holds the old `ra`.

After the delay slot, control goes to `0x8002fb9c`. The body at `0x8002fb9c` is not traced. The words at `0x80010fdc` are not traced. Both addresses are inside the text image, `0x80010000` through `0x800c57ff`. This note does not close the gap in `components/exe/load.cpp`.

## Our code

`components/exe/call_80010fbc.cpp` stores `0x800c005c` at offset `0x68`, then calls `call_8002fb9c` with the words from [table-8009f0b4.md](table-8009f0b4.md). The delay slot does not write `a1`. The callee does not read it. The return at `0x80010fdc` is not traced. No ledger row is added.
