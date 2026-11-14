# Call at 0x8004dee8

No traced entry reaches this address. The prologue saves `ra`. `jal` targets `0x8004dbfc` and would set `ra` to `0x8004def8`. The delay slot is `nop`. No note names `0x8004dbfc`. This note stops at that call and does not enter it.

The 16 bytes from `0x8004dee8` through `0x8004def4` occur once.

## Our code

`call_8004dee8` does not enter `0x8004dbfc`. The host check calls it.

## Gap

`0x8004dbfc` is unnamed.
