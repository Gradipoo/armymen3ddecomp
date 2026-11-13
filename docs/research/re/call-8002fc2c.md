# Function at 0x8002fc2c

Traced fact from the USA PS-X EXE. Re-check on a disc you own with `python3 tools/entry_disasm.py build/disc/SLUS_004.91 --start 0x8002fc2c`. The executable and the listing stay in `build/`. That tool stops at the first jump, the `jal` at `0x8002fc4c`. Re-check the delay slot with `--start 0x8002fc50`. That run's first instruction is the `sw`. The words after that instruction are not traced.

The start address is `0x8002fc2c`. The inventory size is 80 bytes. This follows the call in [call-80010cc4.md](call-80010cc4.md). On arrival `a0` is the object and `a1` is the second argument. `ra` is `0x80010cd0`. The caller's frame stays open. This function does not read it. This note covers 10 instructions, including the delay slot, and stops at the first unnamed `jal`. The hard cap is 64 instructions.

`addiu` at `0x8002fc2c` subtracts `0x20` from `sp`. `sw` at `0x8002fc30` saves the arriving `s1` at `0x14(sp)`. `addu` at `0x8002fc34` then copies `a0` into `s1`. `sw` at `0x8002fc38` saves the arriving `s0` at `0x10(sp)`. `addu` at `0x8002fc3c` then copies `a1` into `s0`. `lui` at `0x8002fc40` sets `v0` to `0x800c0000`. `addiu` at `0x8002fc44` adds `0x5c`, so `v0` becomes `0x800c005c`. `sw` at `0x8002fc48` saves the arriving `ra` at `0x18(sp)`.

`jal` at `0x8002fc4c` targets `0x800302a4` and sets `ra` to `0x8002fc54`. The delay slot at `0x8002fc50` is `sw v0, 0x68(s1)`. It stores `0x800c005c` at offset `0x68` of the object. That replaces the word `0x800be768` stored by the function at `0x80010c90`. `a0` stays the object. `a1` stays the second argument. `python3 tools/sdk_match.py build/disc/SLUS_004.91` does not name `0x800302a4`. The BIOS table in [bios.md](bios.md) does not name it. This note does not enter that body.

This block writes `sp`, the saved slots, `s0`, `s1`, `v0`, and `ra`, and the word at `0x68(s1)`. It reads `sp`, the arriving `s0`, the arriving `s1`, the arriving `ra`, `a0`, and `a1`. It does not read the arriving `v0`, `a2`, or `a3`. It does not write `a0` or `a1`. `s1` leaves as the object. `s0` leaves as the second argument. `v0` leaves as `0x800c005c`. `ra` leaves as `0x8002fc54`. The slot at `0x10(sp)` holds the old `s0`. The slot at `0x14(sp)` holds the old `s1`. The slot at `0x18(sp)` holds `0x80010cd0`.

After the delay slot, control goes to `0x800302a4`. The body at `0x800302a4` is not traced. The words at `0x8002fc54` are not traced. Both addresses are inside the text image, `0x80010000` through `0x800c57ff`. This note does not close the gap in `components/exe/load.cpp`.

## Our code

`components/exe/call_8002fc2c.cpp` stores `0x800c005c` at offset `0x68` of the object. It does not enter `0x800302a4`. That call stays marked in the source. A host check covers the store and leaves the other object bytes unchanged. It does not execute the retail callee. No ledger row is added.
