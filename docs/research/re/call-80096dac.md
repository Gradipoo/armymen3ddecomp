# Call at 0x80096dac

No traced entry reaches this address. `v0` is `0x4b`. The stores write `0x4b` at `a0+0x37`, 0 at `a0+0x2c`, and 0 at `a0+0x36`. `a0` is not stated. `jr ra` returns `0x4b`. The arriving `ra` is not stated.

The 20 bytes from `0x80096dac` through `0x80096dbc` occur once.

## Our code

`call_80096dac` returns `0x4b` and keeps those values. The host check expects that.

## Gap

This boot does not reach `0x80096dac`.
