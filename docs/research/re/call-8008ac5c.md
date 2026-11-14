# Call at 0x8008ac5c

No traced entry reaches this address. `a0` is not stated. The stores write 3 at `a0+3` and `0x40` at `a0+7`. `jr ra` returns `0x40`. The arriving `ra` is not stated.

The 20 bytes from `0x8008ac5c` through `0x8008ac6c` occur once.

## Our code

`call_8008ac5c` returns `0x40` and keeps those bytes. The host check expects 3 and `0x40`.

## Gap

This boot does not reach `0x8008ac5c`.
