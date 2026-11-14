# Call at 0x8005cbfc

No traced entry reaches this address. `lw` reads the word at `a0` plus 4 into `a2`. `a0` is not stated, so that word is not stated. `bgez` compares it with 0 and targets `0x8005cc48`. This note does not guess that side. The delay slot writes 0 into `v1`. The words after the delay slot are not traced.

The 16 bytes from `0x8005cbfc` through `0x8005cc08` occur once.

## Our code

`call_8005cbfc` does not take the branch. The host check calls it.

## Gap

The word at the arriving `a0` plus 4 is not stated, so the `bgez` stays open.
