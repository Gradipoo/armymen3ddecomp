# Call at 0x8004edf8

No traced entry reaches this address. `lui` and `addiu` build `0x800aed80` in `v1`. `lw` reads the word at `0x800aed8c`. That word is not stated. `sw` writes `0x800aed80` at `0x800aedd4`. `sh` writes -256, -120, 512, and 240 at the loaded address plus 0, 2, 4, and 6. `jr` returns. The delay slot writes 240. The arriving `ra` is not stated.

The 68 bytes from `0x8004edf8` through `0x8004ee38` occur once.

## Our code

`call_8004edf8` records the four halfwords. The host check expects -256, -120, 512, and 240.

## Gap

The word at `0x800aed8c` is not stated, so the stored address is not fixed. The arriving `ra` is not stated.
