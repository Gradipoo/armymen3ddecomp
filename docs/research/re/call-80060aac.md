# Call at 0x80060aac

`call-80025470.md` calls here. `a0` arrives as `0x800d0000`. `ra` arrives as `0x80025478`. `v0` arrives as 0. `s0` arrives as `0x8009f510`. The caller is still inside the function at 0x800251f8. The saved `ra` of that frame stays `0x8007faec`. This note does not state `a1`.

`python3 tools/entry_disasm.py EXE --start 0x80060aac` followed 24 instructions and stopped at the first jump. The delay slot is one more instruction. This note re-checks it with `--start 0x80060b0c`.

`addiu sp, sp, -0x18` at 0x80060aac opens a frame of 0x18. This note does not state the absolute `sp`.

`addiu a0, zero, 0x1000` at 0x80060ab0 writes `0x1000` into `a0`. It does not read the arriving `a0`.

`lui v0, 0x800b` at 0x80060ab4 writes `0x800b0000` into `v0`. It does not read the arriving `v0`.

`sw zero, 0x593c(v0)` at 0x80060ab8 stores 0 at `0x800b593c`. That address is inside the text image. No earlier traced block stores it. This note does not read the executable word.

`lui v0, 0x800e` at 0x80060abc writes `0x800e0000` into `v0`. It does not load the word at `0x800e0000`.

`sh zero, -0x2d08(v0)` at 0x80060ac0 stores the halfword 0 at `0x800dd2f8`.

`addiu v0, v0, -0x2d08` at 0x80060ac4 writes `0x800dd2f8` into `v0`.

`addu v1, a0, zero` at 0x80060ac8 copies `a0` into `v1`. `v1` is `0x1000`.

`sw ra, 0x14(sp)` at 0x80060acc saves `0x80025478`. `sw s0, 0x10(sp)` at 0x80060ad0 saves `0x8009f510`. Those slots are in this new frame. The saved `ra` at 0x800251f8 stays `0x8007faec`.

`sh v1, 0x4(v0)` at 0x80060ad4 stores the halfword `0x1000` at `0x800dd2fc`.

`addiu v1, zero, -0x1000` at 0x80060ad8 writes `0xfffff000` into `v1`.

The next stores use `v0` as `0x800dd2f8`:

- `sh zero, 0x2(v0)` at 0x80060adc stores 0 at `0x800dd2fa`.
- `sh zero, 0x6(v0)` at 0x80060ae0 stores 0 at `0x800dd2fe`.
- `sh zero, 0x8(v0)` at 0x80060ae4 stores 0 at `0x800dd300`.
- `sh v1, 0xa(v0)` at 0x80060ae8 stores the low half of `v1`, `0xf000`, at `0x800dd302`.
- `sh zero, 0xc(v0)` at 0x80060aec stores 0 at `0x800dd304`.
- `sh zero, 0xe(v0)` at 0x80060af0 stores 0 at `0x800dd306`.
- `sh zero, 0x10(v0)` at 0x80060af4 stores 0 at `0x800dd308`.

`lui v0, 0x800e` at 0x80060af8 writes `0x800e0000` into `v0` again. `addiu v0, v0, -0x2d48` at 0x80060afc writes `0x800dd2b8` into `v0`.

`sh zero, 0x4(v0)` at 0x80060b00 stores 0 at `0x800dd2bc`. `sh zero, 0xa(v0)` at 0x80060b04 stores 0 at `0x800dd2c2`.

The halfword addresses are inside the zero fill from `entry-after-zero.md`. No earlier traced block stores them.

`jal` at 0x80060b08 targets `0x80060b58`. `tools/sdk_names.txt` and `docs/research/re/bios.md` do not name that address. No note reaches its `jr ra`. The slice enters it. This note does not. `ra` becomes `0x80060b10`. `a0` is `0x1000` at the call. This note does not state `a1`.

The delay slot at 0x80060b0c is `sh zero, 0x10(v0)`. It stores 0 at `0x800dd2c8`. It does not write `a0` or `v0`.

`v0` leaves as `0x800dd2b8`. `v1` leaves as `0xfffff000`. `s0` stays `0x8009f510`. `s1` stays `0x8009f820`. `s2` stays `0x80080000`. The word at `0x800c5460` stays `0x800d1598`. The word at `0x8007f9a8` stays 0. The word at `0x800e1a04` stays `0x100`. The word at `0x800e19ec` stays 1. The word at `0x800e19f0` stays `0x8000`. The word at `0x800e15b0` stays 2. This note does not state the word at `0x800e19e8`. Which path reached the `jal` at 0x8002525c is still unknown.

The 100 bytes from 0x80060aac through 0x80060b0c occur once in the executable.

## Our code

`components/exe/call_80060aac.cpp` writes `0x1000` into `a0` and stores the word and halfwords above. The nine halfwords are the ones from `0x800dd2f8`. The three later halfwords are `0x800dd2bc`, `0x800dd2c2`, and `0x800dd2c8`. It then calls `call_80060b58`, which stores `0x1000` in the six halfwords from that note. The return is `call_80060b10`. That call writes `0x800dd2d8` into `s0` and `a0`, `0x1000` into `a1` and `a3`, and `0xa00` into `a2`. `call_80060b10` calls `call_8007abf8`. The return at `0x80060b2c` stays open. The file does not name those addresses.

## Gap

The return at `0x80060b2c` stays open. `a0` is `0x800dd2d8`. `a1` is `0x1000`. `a2` is `0xa00`. `a3` is `0x1000`.
