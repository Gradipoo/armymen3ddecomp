# Call at 0x8007a3bc

Traced fact from the USA PS-X EXE. Re-check on a disc you own with
`python3 tools/entry_disasm.py build/disc/SLUS_004.91 --start 0x8007a3bc`.
The executable and the listing stay in `build/`.

This is the return site after the `jal` in [call-8007a3b0.md](call-8007a3b0.md).
The callee is [call-8007a2b0.md](call-8007a2b0.md). Arriving `v0` is 0. The
stack slot at `sp+0x10` is 0. The word at `0x8009f380` is 1. `s0` is 1.
`s2` is 0 and `s3` is `0x80010db0`. The frame opened at `0x8007a384` is
still open. The saved `ra` at `0x28(sp)` is `0x80010e24`.

The start address is `0x8007a3bc`. The tool follows straight-line words
until the first branch. It followed 1 instruction and stopped at the
`beq`. The hard cap is 64 instructions. This arrival takes the branch, so
there is no `jal` or `jalr` on the path. This note continues through
`jr ra`. The delay slot is the next word, at `0x8007a3c0`. Re-check it
with `--start 0x8007a3c0`. That run's first instruction is the `addu`.
The taken path is 9 instructions, below the cap.

`beq` at `0x8007a3bc` compares `v0` with zero. `v0` is 0, so the branch to
`0x8007a3e0` is taken. The delay slot at `0x8007a3c0` copies `s0` into
`v0`, so `v0` is 1.

`lw` at `0x8007a3e0` loads the saved `ra` from `0x28(sp)`, so `ra` is
`0x80010e24`.

`lw` at `0x8007a3e4` reloads `s3` from `0x24(sp)`. `lw` at `0x8007a3e8`
reloads `s2` from `0x20(sp)`. `lw` at `0x8007a3ec` reloads `s1` from
`0x1c(sp)`. `lw` at `0x8007a3f0` reloads `s0` from `0x18(sp)`. Those four
slots hold the registers that arrived at `0x8007a384`. This note does not
quote those saved values. The reload of `s0` does not change `v0`. `v0`
stays 1.

`jr` at `0x8007a3f4` returns through `ra`. `ra` is `0x80010e24`. The delay
slot at `0x8007a3f8` adds `0x30` to `sp`, which closes the frame. `v0`
stays 1.

The words at `0x8007a3c4` are the other side of the `v0` test. This
arrival does not enter them. They load the stack slot into `a0` and
`jalr` through `s3`. `s3` is `0x80010db0`. The delay slot would copy `s2`
into `a1`, so `a1` would be 0. `python3 tools/sdk_match.py` has no name
for `0x80010db0`. The BIOS table in [bios.md](bios.md) has no name for it.
That `jalr` would set `ra` to `0x8007a3d0`. The body is not entered.

These words on the taken path read `v0`, `s0`, and `sp`. They write `v0`,
`ra`, `s0`, `s1`, `s2`, `s3`, and `sp`. They do not read the stack slot or
the word at `0x8009f380`. There is no named call. The next address is
`0x80010e24`.

## Our code

`components/exe/call_8007a3bc.cpp` returns `s0` when `v0` is 0. On this
arrival that value is 1. The nonzero side stays a gap in the file. A host
check uses `v0` 0 and `s0` 1. The check does not run the retail `jalr`.
