# Call at 0x80030dac

No traced entry reaches this address. `a0` is not stated. The stores write `a1` at `a0+0x18`, `a2` at `a0+0x1c`, and `a3` at `a0+0x20`. `jr ra` does not write `v0`. The arriving `ra` is not stated.

The 16 bytes from `0x80030dac` through `0x80030db8` occur once.

## Our code

`call_80030dac` keeps the three values. The host check expects 1, 2, and 3.

## Gap

This boot does not reach `0x80030dac`.
