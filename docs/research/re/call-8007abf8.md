# Call at 0x8007abf8

`call-80060b10.md` calls here. `a0` arrives as `0x800dd2d8`. `a1` arrives as `0x1000`. `a2` arrives as `0xa00`. `a3` arrives as `0x1000`. `ra` arrives as `0x80060b2c`. `v0` arrives as `0x800dd2b8`. `v1` arrives as `0xfffff000`. `s0` arrives as `0x800dd2d8`. The caller frame at 0x80060aac saves `ra` `0x80025478`. The frame at 0x800251f8 stays open. Its saved `ra` stays `0x8007faec`.

`python3 tools/entry_disasm.py EXE --start 0x8007abf8` followed 12 instructions and stopped at the first jump. The delay slot is one more instruction. This note re-checks it with `--start 0x8007ac28`.

The stores use `a0` as `0x800dd2d8`. Each `sh` writes the low half of its source:

- `sh a1, 0x0(a0)` at 0x8007abf8 stores `0x1000` at `0x800dd2d8`.
- `sh zero, 0x2(a0)` at 0x8007abfc stores 0 at `0x800dd2da`.
- `sh zero, 0x4(a0)` at 0x8007ac00 stores 0 at `0x800dd2dc`.
- `sh zero, 0x6(a0)` at 0x8007ac04 stores 0 at `0x800dd2de`.
- `sh a2, 0x8(a0)` at 0x8007ac08 stores `0xa00` at `0x800dd2e0`.
- `sh zero, 0xa(a0)` at 0x8007ac0c stores 0 at `0x800dd2e2`.
- `sh zero, 0xc(a0)` at 0x8007ac10 stores 0 at `0x800dd2e4`.
- `sh zero, 0xe(a0)` at 0x8007ac14 stores 0 at `0x800dd2e6`.
- `sh a3, 0x10(a0)` at 0x8007ac18 stores `0x1000` at `0x800dd2e8`.

`sw zero, 0x1c(a0)` at 0x8007ac1c stores 0 at `0x800dd2f4`. `sw zero, 0x18(a0)` at 0x8007ac20 stores 0 at `0x800dd2f0`.

`jr ra` at 0x8007ac24 returns to `0x80060b2c`. The delay slot at 0x8007ac28 is `sw zero, 0x14(a0)`. It stores 0 at `0x800dd2ec`. It does not write `a0`.

These addresses are inside the zero fill from `entry-after-zero.md`. The word at `0x800dd2f4` ends before the halfwords at `0x800dd2f8` from `call-80060aac.md`. This block does not store the two bytes at `0x800dd2ea` and `0x800dd2eb`. No earlier traced block stores them, so they stay 0 from that fill. The halfwords from `call-80060aac.md` and `call-80060b58.md` stay as those notes left them.

`a0`, `a1`, `a2`, and `a3` stay as they arrived. `v0` stays `0x800dd2b8`. `v1` stays `0xfffff000`. `s0` stays `0x800dd2d8`. `s1` stays `0x8009f820`. `s2` stays `0x80080000`. `ra` stays `0x80060b2c`. The saved `ra` in the frame at 0x80060aac stays `0x80025478`. The saved `ra` in the frame at 0x800251f8 stays `0x8007faec`. The word at `0x800b593c` stays 0. The word at `0x800c5460` stays `0x800d1598`. The word at `0x8007f9a8` stays 0. The word at `0x800e1a04` stays `0x100`. The word at `0x800e19ec` stays 1. The word at `0x800e19f0` stays `0x8000`. The word at `0x800e15b0` stays 2. This note does not state the word at `0x800e19e8`. Which path reached the `jal` at 0x8002525c is still unknown.

The 52 bytes from 0x8007abf8 through 0x8007ac28 occur once in the executable. `tools/sdk_names.txt` and `docs/research/re/bios.md` do not name this entry. There is no `jal` or `jalr` in this span.

## Our code

`components/exe/call_8007abf8.cpp` stores the low halves of `a1`, `a2`, and `a3`, and the zeros above. The nine halfwords are the ones from `0x800dd2d8` through `0x800dd2e8`. The three words are `0x800dd2ec`, `0x800dd2f0`, and `0x800dd2f4`. The file does not name those addresses.

## Gap

This span returns. The next note starts at `0x80060b2c` in the caller.
