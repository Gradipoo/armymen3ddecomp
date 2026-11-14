# Block at 0x80088afc

Traced fact from the USA PS-X EXE. Re-check on a disc you own with `python3 tools/entry_disasm.py build/disc/SLUS_004.91 --start 0x80088afc`. The executable and the listing stay in `build/`.

The start address is `0x80088afc`. It is not in `tools/sdk_names.txt`. `python3 tools/sdk_match.py` does not name it. The `jal` in [call-80088360.md](call-80088360.md) calls here and sets `ra` to `0x8008838c`. On arrival `a0` is the word at `0x800b7598`. This note does not quote that word. `a1` is `0x800e160c`. `a2` is `0x40`. `a3` is 0. The tool followed 3 instructions and stopped at the first named `jal`. The hard cap is 64 instructions. This block ended before the cap.

`addiu` opens a frame of `0x18` and saves `ra` at `0x10(sp)`. `jal` at `0x80088b04` targets `0x8008549c` and sets `ra` to `0x80088b0c`. The delay slot sets `a0` to `-1`. `python3 tools/sdk_match.py` names `0x8008549c` `VSync`. The body is not entered.

After the delay slot, control goes to `VSync`. `a0` is `-1`. `a1` stays `0x800e160c`. `a2` stays `0x40`. `a3` stays 0. The saved `ra` at `0x10(sp)` is `0x8008838c`. The words at `0x80088b0c` are not traced. The display x and y halfwords are still not quoted. This note does not close the gap in `components/exe/load.cpp`.
