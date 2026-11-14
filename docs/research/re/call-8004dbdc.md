# Call at 0x8004dbdc

No traced entry reaches this address. The prologue saves `ra`. `jal` targets `0x8004974c` and would set `ra` to `0x8004dbec`. The delay slot is `nop`. No note names `0x8004974c`. This note stops at that call and does not enter it.

The 16 bytes from `0x8004dbdc` through `0x8004dbe8` occur once.

## Our code

`call_8004dbdc` does not enter `0x8004974c`. The host check calls it.

## Gap

`0x8004974c` is unnamed.
