# Call at 0x8004ff0c

No traced entry reaches this address. The prologue subtracts `0x18` from `sp` and copies `a0` into `v1`. `beq` compares `v1` with 0 and targets `0x8004ff48`. `a0` is not stated, so this note does not guess that side. The delay slot saves `ra`. The words after the delay slot are not traced.

The 16 bytes from `0x8004ff0c` through `0x8004ff18` occur once.

## Our code

`call_8004ff0c` does not take the branch. The host check calls it.

## Gap

`a0` is not stated, so the `beq` stays open.
