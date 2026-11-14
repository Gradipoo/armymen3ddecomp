# Call at 0x80043cdc

No traced entry reaches this address. `addu` writes 0 into `a3`. `addiu` writes 1 into `a2`. `addiu` adds `0x2a0` to `a0`. `addiu` writes `0xe` into `v1`. `lhu` reads the halfword at the new `a0`. The arriving `a0` is not stated, so the halfword is not stated. `and` keeps the bits that are also in `a1`. `a1` is not stated. `beq` compares the result with 0 and targets `0x80043d04`. This note does not guess that side. The delay slot adds 2 to `a0`. The words after the delay slot are not traced.

The 36 bytes from `0x80043cdc` through `0x80043cfc` occur once.

## Our code

`call_80043cdc` does not take the branch. The host check calls it.

## Gap

The halfword and `a1` are not stated, so the `beq` stays open.
