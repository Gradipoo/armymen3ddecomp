# Call at 0x80052bdc

No traced entry reaches this address. The prologue saves `s0` and `ra` and copies `a0` into `s0`. `lw` reads the word at `a0` plus `0x1a8`. `a0` is not stated, so that word is not stated. `addiu` writes 1 into `v0`. `beq` compares the loaded word with 0 and targets `0x80052c14`. This note does not guess that side. The delay slot stores 1 at `a0` plus `0x1fc`. The words after the delay slot are not traced.

The 32 bytes from `0x80052bdc` through `0x80052bf8` occur once.

## Our code

`call_80052bdc` does not take the branch. The host check calls it.

## Gap

The word at the arriving `a0` plus `0x1a8` is not stated, so the `beq` stays open.
