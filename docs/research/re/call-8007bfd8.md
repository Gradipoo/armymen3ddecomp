# Call at 0x8007bfd8

No traced entry reaches this address. `a1` is `0x800e1818`. `lw` reads the word at `0x800e181c`. That word is not stated. `andi` keeps bit 2. `beq` compares that bit with 0 and targets `0x8007c004`. This note does not guess that side. The delay slot writes 0 into `v1`. The words after the delay slot are not traced.

The 28 bytes from `0x8007bfd8` through `0x8007bff0` occur once.

## Our code

`call_8007bfd8` does not take the branch. The host check calls it.

## Gap

The word at `0x800e181c` is not stated, so the `beq` stays open.
