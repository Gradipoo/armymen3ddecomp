# Call at 0x8008dabc

No traced entry reaches this address. `addiu` writes `0xa0` into `t2`. `jr` jumps through `t2`. The delay slot writes `0x44` into `t1`. This is the A table. [bios.md](bios.md) does not name that number. This note does not enter the table.

The 12 bytes from `0x8008dabc` through the delay slot occur once.

## Our code

`call_8008dabc` keeps the table and the number. The host check expects both.

## Gap

[bios.md](bios.md) does not name A function `0x44`.
