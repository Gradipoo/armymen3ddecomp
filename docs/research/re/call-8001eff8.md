# Function at 0x8001eff8

Traced fact from the USA PS-X EXE. Re-check on a disc you own with `python3 tools/entry_disasm.py build/disc/SLUS_004.91 --start 0x8001eff8`. The executable and the listing stay in `build/`. That tool stops at the first jump, the `jal` at `0x8001f008`. Re-check the delay slot with `--start 0x8001f00c`. That run's first instruction is the `addiu`. The words after that instruction are not traced.

The start address is `0x8001eff8`. The inventory size is 56 bytes. No note cites a caller, so the arriving `ra` is not known. The tool followed 5 instructions and stopped at the `jal`. This note covers 6 instructions, including the delay slot, and stops at the first unnamed `jal`. The hard cap is 64 instructions. There is no `jr` in this span. There is no branch before the call.

`addiu` at `0x8001eff8` subtracts `0x18` from `sp`. `sw` at `0x8001effc` saves the arriving `s0` at `0x10(sp)`. `addu` at `0x8001f000` copies `a0` into `s0`. `sw` at `0x8001f004` saves the arriving `ra` at `0x14(sp)`.

`jal` at `0x8001f008` targets `0x800374b0` and sets `ra` to `0x8001f010`. The delay slot at `0x8001f00c` writes 1 into `a1`. The delay slot does not write `a0`, `a2`, or `a3`. `python3 tools/sdk_match.py build/disc/SLUS_004.91` does not name `0x800374b0`. The BIOS table in [bios.md](bios.md) does not name it. This note does not enter that body. `a0` stays the first argument. `a1` at the call is 1. This block does not write `a2` or `a3`. They stay as they arrived. This note does not treat them as further arguments of the call. `0x800374b0` is inside the text image, `0x80010000` through `0x800c57ff`. This block does not load the word at `0x800374b0`. `0x8001f010` is inside that same image. This block does not load the word at `0x8001f010`.

This block writes `sp`, the two saved slots, `s0`, `a1`, and `ra`. It reads `sp`, the arriving `s0` and `ra`, and `a0`. It does not read `a1`, `a2`, or `a3` on arrival. The saved `ra` stays the arriving `ra`. `s0` stays the first argument. `a0` leaves as the first argument. `a1` leaves as 1. `ra` leaves as `0x8001f010`. `v0` stays unknown.

After the delay slot, control goes to `0x800374b0`. `a0` is the first argument. `a1` is 1. `s0` is the first argument. `ra` is `0x8001f010`. The words at `0x8001f010` are not traced. This note does not close the gap in `components/exe/load.cpp`.
