# Call at 0x8008ac3c

No traced entry reaches this address. `sll` shifts `a1` left by 6. `sra` shifts `a0` right by 4. `andi` keeps `0x3f` of that shift. `or` joins the two values. `jr ra` returns the low 16 bits. `a0` and `a1` are not stated.

The 24 bytes from `0x8008ac3c` through `0x8008ac50` occur once.

## Our code

`call_8008ac3c` returns that halfword. The host check uses `a0` `0x10` and `a1` 1 and expects `0x41`.

## Gap

This boot does not reach `0x8008ac3c`.
