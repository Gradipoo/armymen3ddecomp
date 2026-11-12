# After the RAM fill

Traced fact from the USA PS-X EXE. Re-check on a disc you own with `python3 tools/entry_disasm.py build/disc/SLUS_004.91 --start 0x8007fa84`. The executable and the listing stay in `build/`.

The start address is `0x8007fa84`. The `jal` at `0x8007fa7c` set `ra` to this address. The tool followed 5 instructions and stopped at the first jump. The hard cap is 64 instructions. This block ended before the cap.

`lui` at `0x8007fa84` loads `0x80080000` into `a0`. `addiu` at `0x8007fa88` adds `-0x628`, so `a0` is `0x8007f9d8`. `lui` at `0x8007fa8c` loads `0x1fc00000` into `a1`. `ori` at `0x8007fa90` ORs in `0x129`, so `a1` is `0x1fc00129`.

`jal` at `0x8007fa94` targets `0x8007fb1c` and sets `ra` to `0x8007fa9c`. The delay slot at `0x8007fa98` is `nop`. Re-check it with `--start 0x8007fa98`. That run stops at the jump at `0x8007fab0`. After the delay slot, control goes to `0x8007fb1c`.

This block writes `a0`, `a1`, and `ra`. The body past this jump is not traced. This note does not close the gap in `components/exe/load.cpp`.
