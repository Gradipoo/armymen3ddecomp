# Call at 0x8007c2dc

Traced fact from the USA PS-X EXE. Re-check on a disc you own with `python3 tools/entry_disasm.py build/disc/SLUS_004.91 --start 0x8007c2dc`. The executable and the listing stay in `build/`.

The start address is `0x8007c2dc`. The `jalr` in [call-8007a668-20.md](call-8007a668-20.md) jumps here. `ra` is `0x8007a6bc`. `a0` is `0x8001004c`. The caller `s1` is 21. The frame at `0x800251f8` stays open. Its saved `ra` stays `0x8007faec`. The word at `0x800b5d38` is 20.

`addiu` at `0x8007c2dc` subtracts `0x18` from `sp`. `lui` at `0x8007c2e0` and `addiu` at `0x8007c2e4` set `a0` to `0x800e18d8`. `sw` at `0x8007c2e8` stores `ra` at `sp+0x10`. `jal` at `0x8007c2ec` targets `0x800973f4`. `tools/sdk_names.txt` names that address `PadInitMtap`. `ra` becomes `0x8007c2f4`. The delay slot sets `a1` to `a0` plus `0x22`, so `a1` is `0x800e18fa`. This note does not enter that body.

The next note starts at `0x8007c2f4`. The caller return at `0x8007faec` is not traced.
