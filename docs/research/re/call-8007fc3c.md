# Call at 0x8007fc3c

No traced entry reaches this address. `mfc0` reads coprocessor 0 register 12 into `a0`. `ori` sets bits 0 and 10 with `0x401`. `mtc0` writes the result back. `jr ra` does not write `v0`. The arriving status and the arriving `ra` are not stated.

The 28 bytes from `0x8007fc3c` through `0x8007fc54` occur once.

## Our code

`call_8007fc3c` returns the status with those bits set. The host check starts at 0 and expects `0x401`.

## Gap

This boot does not reach `0x8007fc3c`. The live status word is not stated.
