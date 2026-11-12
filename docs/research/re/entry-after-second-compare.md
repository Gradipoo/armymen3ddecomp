# After the second byte compare

Traced fact from the USA PS-X EXE. Re-check on a disc you own with `python3 tools/entry_disasm.py build/disc/SLUS_004.91 --start 0x8007fab8`. The executable and the listing stay in `build/`.

The start address is `0x8007fab8`. The `jal` at `0x8007fab0` set `ra` to this address. That call is in [entry-after-compare.md](entry-after-compare.md). The tool followed 6 instructions and stopped at the first jump. The hard cap is 64 instructions. This block ended before the cap.

`or` at `0x8007fab8` writes `t0` as `t0` OR `v0`. `t0` still holds the first compare result, and `v0` is the result of the call that returned here. The blocks in [entry-bios-call.md](entry-bios-call.md) and [entry-byte-compare.md](entry-byte-compare.md) do not write `t0`. Which values this boot has is unknown, because the BIOS ROM is not in this tree. This block does not branch on `t0` or `v0`.

`lui` at `0x8007fabc` loads `0x80080000` into `a0`. `addiu` at `0x8007fac0` adds `-0x614`, so `a0` is `0x8007f9ec`. `lui` at `0x8007fac4` loads `0x1fc00000` into `a1`. `ori` at `0x8007fac8` ORs in `0x12c`, so `a1` is `0x1fc0012c`.

`jal` at `0x8007facc` targets `0x8007fb1c` and sets `ra` to `0x8007fad4`. The delay slot at `0x8007fad0` is `nop`. Re-check it with `--start 0x8007fad0`. After the delay slot, control goes to `0x8007fb1c`. The `or` result does not change that target. The only branch or jump in this block is that `jal`.

This block writes `t0`, `a0`, `a1`, and `ra`. It reads `v0` and does not write it. `0x8007f9ec` sits `0xc` bytes before the entry at `0x8007f9f8`. `a1` is `0x12c` bytes into the BIOS ROM. That ROM is not in this tree. The callee is the block in [entry-bios-call.md](entry-bios-call.md). Whether the new bytes match stays open. The return continues in [entry-after-third-compare.md](entry-after-third-compare.md). This note does not close the gap in `components/exe/load.cpp`.
