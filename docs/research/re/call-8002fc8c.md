# Function at 0x8002fc8c

Traced fact from the USA PS-X EXE. Re-check on a disc you own with `python3 tools/entry_disasm.py build/disc/SLUS_004.91 --start 0x8002fc8c`. The executable and the listing stay in `build/`. That tool stops at the first jump, the `jal` at `0x8002fc94`. Re-check the delay slot with `--start 0x8002fc98`. That run's first instruction is the `sw`. The words after that instruction are not traced.

The start address is `0x8002fc8c`. The inventory size is 32 bytes. This note has no boot caller. The incoming `a0` is a pointer. The incoming `a1` is stored through it. Their values are not known. This note covers 4 instructions, including the delay slot, and stops at the first unnamed `jal`. The hard cap is 64 instructions. There is no branch and no `jr` in this span.

`addiu` at `0x8002fc8c` subtracts `0x18` from `sp`. `sw` at `0x8002fc90` saves the arriving `ra` at `0x10(sp)`. That store happens before the `jal` writes `ra`.

`jal` at `0x8002fc94` targets `0x8002fb50` and sets `ra` to `0x8002fc9c`. The delay slot at `0x8002fc98` stores `a1` at `0x0(a0)`. It does not write `a0`, `a1`, `a2`, or `a3`. At the call, `a0` is the incoming pointer and `a1` is the incoming second argument. The store completes before the callee runs. `python3 tools/sdk_match.py build/disc/SLUS_004.91` does not name `0x8002fb50`. The BIOS table in [bios.md](bios.md) does not name it. [call-80010f84.md](call-80010f84.md) records a different call. This note does not enter that body.

This block writes `sp`, `ra`, the saved slot, and the word at offset `0` of `a0`. It reads `sp`, the arriving `ra`, `a0`, and `a1`. It does not read `a2` or `a3`. It does not write `a0`, `a1`, `a2`, `a3`, or `v0`. The slot at `0x10(sp)` holds the arriving `ra`. `a0` stays the incoming pointer. `a1` stays the incoming second argument. `ra` leaves as `0x8002fc9c`. `sp` is `0x18` below the arrival value. `v0` stays unknown.

After the delay slot, control goes to `0x8002fb50`. The next address is `0x8002fb50`. The words at `0x8002fc9c` are not traced. Both addresses are inside the text image, `0x80010000` through `0x800c57ff`. This block does not load the word at `0x8002fb50`. This block does not load the word at `0x8002fc9c`. This prefix is not the whole function. This note does not close the gap in `components/exe/load.cpp`.

## Our code

No source file is added for this function. The store at offset `0` is traced above. The unnamed `jal` is the stop. No ledger row is added.
