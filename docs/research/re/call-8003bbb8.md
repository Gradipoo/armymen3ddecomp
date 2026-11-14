# Call at 0x8003bbb8

No traced entry reaches this address. The prologue saves `s0`, `s1`, and `ra`, and copies `a0` into `s0` and `a1` into `s1`. `lw` reads the word at `a0` plus 8. `a0` is not stated, so that word is not stated. `addiu` builds `0x800c0c34` in `v0`. `beq` compares the loaded word with 0 and targets `0x8003bbec`. This note does not guess that side. The delay slot stores `0x800c0c34` at `s0` plus `0x44`. The words after the delay slot are not traced.

The 44 bytes from `0x8003bbb8` through `0x8003bbe0` occur once.

## Our code

`call_8003bbb8` does not take the branch. The host check calls it.

## Gap

The word at the arriving `a0` plus 8 is not stated, so the `beq` stays open.
