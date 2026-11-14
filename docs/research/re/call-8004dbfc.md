# Call at 0x8004dbfc

[call-8004dee8.md](call-8004dee8.md) reaches this address. `a0` and `a1` are not stated. `ra` would be `0x8004def8`.

The prologue saves `s0`, `s1`, and `ra` and copies `a0` into `s0`. `lh` reads the halfword at `s0+0x114`. That halfword is not stated. `beq` at `0x8004dc18` compares it with 0 and targets `0x8004dc74`. This note does not guess that side. The delay slot copies `a1` into `s1`. The words after the delay slot are not traced.

The 36 bytes from `0x8004dbfc` through `0x8004dc1c` occur once.

## Our code

`call_8004dbfc` does not take the branch. The host check calls it.

## Gap

The halfword at `a0+0x114` is not stated, so the `beq` stays open.
