# Call at 0x8007cb9c

Traced fact from the USA PS-X EXE. Re-check on a disc you own with `python3 tools/entry_disasm.py build/disc/SLUS_004.91 --start 0x8007cb9c`. The executable and the listing stay in `build/`.

The start address is `0x8007cb9c`. The `jalr` in [call-8007a668-12.md](call-8007a668-12.md) jumps here. `ra` is `0x8007a6bc`. `a0` is `0x80010060`. The caller `s1` is 13. The frame at `0x800251f8` stays open. Its saved `ra` stays `0x8007faec`.

`addiu` at `0x8007cb9c` subtracts `0x18` from `sp`. `sw` at `0x8007cba0` stores `ra` at `sp+0x10`. `jal` at `0x8007cba4` targets `0x8008624c`. `tools/sdk_names.txt` names that address `ResetGraph`. `ra` becomes `0x8007cbac`. The delay slot clears `a0`, so `a0` is 0. This note does not enter that body.

The next note starts at `0x8007cbac`. The caller return at `0x8007faec` is not traced.
