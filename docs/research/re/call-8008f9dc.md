# Call at 0x8008f9dc

No traced entry reaches this address. `v0` is `0xffffffff`. `jr ra` returns that value. The delay stores it at `0x800bcdf8`. That address is below the zero fill in [entry-after-fill.md](entry-after-fill.md). The executable word is already `0xffffffff`. No traced note stores it. The arriving `ra` is not stated.

The 16 bytes from `0x8008f9dc` through `0x8008f9e8` occur once.

## Our code

`call_8008f9dc` returns `0xffffffff` and stores it. The host check expects that.

## Gap

This boot does not reach `0x8008f9dc`.
