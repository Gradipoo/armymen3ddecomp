# Call at 0x8003fec8

No traced entry reaches this address. The prologue subtracts `0x28` from `sp` and saves `ra`. `lw` reads the word at `a0` into `t2`. `lhu` reads the halfword at `a0` plus `0xc8`. `a0` is not stated, so both are not stated. `sh` writes that halfword at `t2` plus `0x48`. `lw` reads the words at `sp` plus `0x38`, `0x3c`, and `0x40`. Those words are not stated. `sw` writes the first two at `sp` plus `0x10` and `0x14`. `jal` at `0x8003fef0` targets `0x80030608` and would set `ra` to `0x8003fef8`. The delay slot writes the third word at `sp` plus `0x18`. No note names `0x80030608`. This note stops at that call and does not enter it.

The 48 bytes from `0x8003fec8` through `0x8003fef4` occur once.

## Our code

`call_8003fec8` does not enter `0x80030608`. The host check calls it.

## Gap

`0x80030608` is unnamed. The arriving `a0` is not stated.
