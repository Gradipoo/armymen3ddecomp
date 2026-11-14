# Call at 0x80049fdc

No traced entry reaches this address. `a1` becomes `a0` plus `0x18`. `v1` is 2. `a0` becomes the arriving `a0` plus `0xb8`. `a2` is -1. The arriving `a0` is not stated, so the copied words are not stated.

The loop reads one word, adds 4 to the source, subtracts 1 from `v1`, and writes the word to the destination. `bne` repeats while `v1` is not -1. The delay slot adds 4 to the destination. `v1` is 1, then 0, then -1. The third compare is not taken. The delay slot still runs. Three words move from the arriving `a0` plus `0xb8`, `0xbc`, and `0xc0` to plus `0x18`, `0x1c`, and `0x20`.

`jr` returns. The delay slot writes 1 into `v0`. The arriving `ra` is not stated.

The 48 bytes from `0x80049fdc` through `0x8004a008` occur once.

## Our code

`call_80049fdc` copies those three words and returns 1. The host check uses a local table.

## Gap

The arriving `a0` and `ra` are not stated.
