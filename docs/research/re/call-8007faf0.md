# Call at 0x8007faf0

Traced fact from the USA PS-X EXE. Re-check on a disc you own with `python3 tools/entry_disasm.py build/disc/SLUS_004.91 --start 0x8007faf0`. The executable and the listing stay in `build/`.

The start address is `0x8007faf0`. The `jal` at `0x80025220` set `ra` to `0x80025228` and jumped here. That call is in [call-800251f8.md](call-800251f8.md). The tool followed 1 instruction and stopped at the first jump. The hard cap is 64 instructions. This block ended before the cap.

`jr` at `0x8007faf0` returns through `ra`. The delay slot at `0x8007faf4` is `nop`. Re-check it with `--start 0x8007faf4`. That run's first instruction is the `nop`. The same run then reaches the fill at `0x8007faf8` and stops at the branch at `0x8007fafc`. Those later instructions are already in [entry-call.md](entry-call.md). This jump does not enter them.

After the delay slot, control goes to `0x80025228`. It does not fall into `0x8007faf8`. `0x8007faf0` is `0x8` bytes before that fill. The return at `0x80025228` is not traced. The caller return at `0x8007faec` is not traced. This note does not close the gap in `components/exe/load.cpp`.
