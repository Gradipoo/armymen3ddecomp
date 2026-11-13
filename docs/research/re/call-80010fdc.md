# Block at 0x80010fdc

Traced fact from the USA PS-X EXE. Re-check on a disc you own with `python3 tools/entry_disasm.py build/disc/SLUS_004.91 --start 0x80010fdc`. The executable and the listing stay in `build/`. That tool stops at the first jump, the `jal` at `0x80010fe8`. Re-check the delay slot with `--start 0x80010fec`. That run's first instruction is the `sw`. The words after that instruction are not traced.

This follows [call-80010fbc.md](call-80010fbc.md). The function entry stays `0x80010fbc`. The inventory size is 72 bytes. The `jal` at `0x80010fd4` calls `0x8002fb9c` and sets `ra` to `0x80010fdc`. [call-8002fb9c.md](call-8002fb9c.md) traces that entry and stops at an unnamed `jal`. It does not reach `jr ra`. This note does not enter that body. The traced prefix does not write `s0`. The words after `0x8002fc1c` are not traced, so this note does not state `s0` on arrival. This note covers 5 instructions, including the delay slot, and stops at the first unnamed `jal`. The hard cap is 64 instructions. There is no `jr`.

`addu` at `0x80010fdc` copies `s0` into `a0`. `lui` at `0x80010fe0` sets `v0` to `0x800c0000`. `addiu` at `0x80010fe4` adds `-0x1898`, so `v0` becomes `0x800be768`.

`jal` at `0x80010fe8` targets `0x80010c7c` and sets `ra` to `0x80010ff0`. The delay slot at `0x80010fec` is `sw v0, 0x68(s0)`. It stores `0x800be768` at offset `0x68` of the pointer in `s0`. The delay slot does not write `a0`, `a1`, `a2`, or `a3`. This block does not write `a1`, `a2`, or `a3`. `python3 tools/sdk_match.py build/disc/SLUS_004.91` does not name `0x80010c7c`. The BIOS table in [bios.md](bios.md) does not name it. This note does not enter that body. `0x80010c7c` is inside the text image, `0x80010000` through `0x800c57ff`. This block does not load the word at `0x80010c7c`. `0x80010ff0` is inside that same image. This block does not load the word at `0x80010ff0`.

This block writes `a0`, `v0`, and `ra`, and the word at `0x68(s0)`. It reads `s0`. It does not read the arriving `v0`. The `addiu` reads the `v0` from the `lui`. It does not read `sp`. It does not write `s0` or `sp`. `a0` leaves as the value copied from `s0`. `v0` leaves as `0x800be768`. `ra` leaves as `0x80010ff0`. This note does not state `a1`, `a2`, `a3`, or the arriving `s0`.

After the delay slot, control goes to `0x80010c7c`. `a0` is the value copied from `s0`. The body at `0x80010c7c` is not traced. The words at `0x80010ff0` are not traced. This note does not close the gap in `components/exe/load.cpp`.

## Our code

`components/exe/call_80010fbc.cpp` stores `0x800c005c` at offset `0x68` and stops at the jal to `0x8002fb9c`. It does not store `0x800be768`. It does not call `0x80010c7c`. No ledger row is added.
