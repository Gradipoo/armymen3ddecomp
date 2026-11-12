# Both paths of the byte compare

Traced fact from the USA PS-X EXE. Re-check on a disc you own with `python3 tools/entry_disasm.py build/disc/SLUS_004.91 --start 0x8007fb2c` and `--start 0x8007fb3c`. The executable and the listing stay in `build/`.

These two addresses are the two paths from the `beq` at `0x8007fb24`. That branch is in [entry-bios-call.md](entry-bios-call.md). Each run stops at the first branch or jump. The hard cap is 64 instructions. Both blocks ended before the cap. The tool followed 3 instructions from `0x8007fb2c` and 1 instruction from `0x8007fb3c`.

`xor` at `0x8007fb2c` sets `v0` to `v0` XOR `v1`. The result is 0 when those values match. `sltu` at `0x8007fb30` sets `v0` to 1 when that result is not 0, and to 0 when it is 0. `beq` at `0x8007fb34` branches to `0x8007fb1c` when `v0` is 0. That outcome loops back to `0x8007fb1c`. When `v0` is not 0, the branch is not taken and execution continues at `0x8007fb3c`. The delay slot at `0x8007fb38` is `addiu a1, a1, 0x1`, so `a1` rises by 1 on both outcomes. Re-check it with `--start 0x8007fb38`. That run stops at the jump at `0x8007fb3c`.

`jr` at `0x8007fb3c` returns through `ra`. This path does not loop back to `0x8007fb1c`. The delay slot at `0x8007fb40` is `xori v0, v0, 0x1`, so `v0` becomes `v0` XOR 1. The body after that word is not traced. The `jal` at `0x8007fa94` set `ra` to `0x8007fa9c`, and these instructions do not write `ra`, so control goes to `0x8007fa9c`.

The path from `0x8007fb24` arrives with `v0` equal to 0, so the delay slot leaves `v0` as 1. It skips `0x8007fb38`, so `a1` stays as it was. The path that continues from `0x8007fb34` arrives with `v0` equal to 1 and with `a1` already increased by 1, so the delay slot leaves `v0` as 0.

On this call the first byte at `a0` is not zero. `a0` is `0x8007f9d8`. The `beq` at `0x8007fb24` is not taken, so this call continues at `0x8007fb2c`. `a1` is `0x1fc00129`, in the BIOS ROM. That ROM is not in this tree. Whether `v0` and `v1` match, and whether `0x8007fb34` loops, stays open. The return continues in [entry-after-compare.md](entry-after-compare.md). This note does not close the gap in `components/exe/load.cpp`.
