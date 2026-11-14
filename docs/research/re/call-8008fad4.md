# Call at 0x8008fad4

No traced entry reaches this address. `lw` reads `0x800bcdf8`. That address is below the zero fill in [entry-after-fill.md](entry-after-fill.md). The executable word is `0xffffffff`. No traced note stores it. `srl` by 31 leaves 1. `jr ra` returns 1. The arriving `ra` is not stated.

The 16 bytes from `0x8008fad4` through `0x8008fae0` occur once.

## Our code

`call_8008fad4` returns the top bit. The host check expects 1.

## Gap

This boot does not reach `0x8008fad4`.
