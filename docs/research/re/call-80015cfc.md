# Call at 0x80015cfc

No traced entry reaches this address. `lw` at `0x80015cfc` reads the word at `a0+0xa0`. `a0` is not stated, and no traced store writes that offset, so the word is not stated. `beq` at `0x80015d04` compares it with 0 and targets `0x80015d60`. This note does not guess that side. The delay slot is `nop`. The words after the delay slot are not traced.

The 12 bytes from `0x80015cfc` through `0x80015d04` occur once.

## Our code

`call_80015cfc` keeps the object pointer and does not take the branch. The host check calls it.

## Gap

The word at `a0+0xa0` is not stated, so the `beq` at `0x80015d04` stays open.
