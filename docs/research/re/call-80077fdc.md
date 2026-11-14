# Call at 0x80077fdc

`call-80025514.md` calls here. `a0` arrives as `0x800638b8`. `a1` arrives as 1. `v0` arrives as 0. `s0` arrives as `0x8009f510`. `s1` arrives as `0x8009f820`. `s2` arrives as `0x8009f820`. `ra` arrives as `0x8002552c`. The frame at 0x800251f8 stays open. Its saved `ra` stays `0x8007faec`. The byte at `0x800638b8` is 0. The word at `0x800d8458` is 1. The word at `0x800dd490` is 2.

`python3 tools/entry_disasm.py EXE --start 0x80077fdc` followed 2 instructions and stopped at `jr ra`. The delay slot is one more instruction. This note re-checks it with `--start 0x80077fe4`.

`lui v0, 0x800e` at 0x80077fdc makes `v0` `0x800e0000`. `jr ra` at 0x80077fe0 returns to `0x8002552c`. The delay slot at 0x80077fe4 is `sw a0, 0x1780(v0)`. It stores `0x800638b8` at `0x800e1780`. That address is inside the zero fill from `entry-after-fill.md`.

`a0` stays `0x800638b8`. `a1` stays 1. `v0` leaves as `0x800e0000`. `s0` stays `0x8009f510`. `s1` stays `0x8009f820`. `s2` stays `0x8009f820`. The word at `0x800d8458` stays 1. The word at `0x800dd490` stays 2. The word at `0x800dd498` stays `0x8005b3d4`. The word at `0x800dd540` stays 5. The word at `0x800be6e8` stays 1. The word at `0x8007f9a8` stays 0. The word at `0x800e1a04` stays `0x100`. The saved `ra` stays `0x8007faec`.

The 12 bytes from 0x80077fdc through 0x80077fe4 occur once. `python3 tools/research_duplicates.py EXE` does not group a function at 0x80077fdc. There is no `jal` or `jalr` in this span.

## Our code

`components/exe/call_80077fdc.cpp` stores `a0` and returns the caller's `ra`. On this entry the stored value is `0x800638b8` and the return address is `0x8002552c`.

## Gap

This span returns. The next note resumes the caller at `0x8002552c`. `v0` is `0x800e0000`. The word at `0x800e1780` is `0x800638b8`. The frame at 0x800251f8 stays open. Its saved `ra` stays `0x8007faec`.
