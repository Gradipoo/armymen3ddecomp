# Call at 0x8008dacc

Traced fact from the USA PS-X EXE. Re-check on a disc you own with `python3 tools/entry_disasm.py build/disc/SLUS_004.91 --start 0x8008dacc`. The executable and the listing stay in `build/`.

The start address is `0x8008dacc`. The `jal` in [call-8007c304.md](call-8007c304.md) jumps here. `ra` is `0x8007c314`. `a0` is 0. The caller `s1` is 20. The frame at `0x800251f8` stays open. Its saved `ra` stays `0x8007faec`.

`addiu` at `0x8008dacc` subtracts `0x18` from `sp`. `sw` at `0x8008dad0` stores `ra` at `sp+0x10`. `jal` at `0x8008dad4` targets `0x8009023c`. `tools/sdk_names.txt` names that address `InitCARD`. `ra` becomes `0x8008dadc`. The delay slot is `nop`. `a0` stays 0. This note does not enter that body.

The next note starts at `0x8008dadc`. The caller return at `0x8007faec` is not traced.
