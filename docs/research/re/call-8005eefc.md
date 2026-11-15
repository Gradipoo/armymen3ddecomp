# Call at 0x8005eefc

No traced entry reaches this address. The prologue saves `ra`. `jal` at `0x8005ef04` targets `0x8005eed4` and would set `ra` to `0x8005ef0c`. The delay slot is `nop`. No note names `0x8005eed4`. This note stops at that call and does not enter it.

The 16 bytes from `0x8005eefc` through `0x8005ef08` occur once.

## Our code

`call_8005eefc` does not enter `0x8005eed4`. The host check calls it.

## Gap

`0x8005eed4` is unnamed.
