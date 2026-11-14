# Call at 0x8007fc1c

No traced entry reaches this address. `mfc0` reads coprocessor 0 register 12 into `a0`. `and` keeps that value with `0xfffffbfe`, which clears bits 1 and 10. `mtc0` writes the result back. `jr ra` does not write `v0`. The arriving status and the arriving `ra` are not stated.

The 32 bytes from `0x8007fc1c` through `0x8007fc38` occur once.

## Our code

`call_8007fc1c` returns the masked status. The host check starts at `0xffffffff` and expects `0xfffffbfe`.

## Gap

This boot does not reach `0x8007fc1c`. The live status word is not stated.
