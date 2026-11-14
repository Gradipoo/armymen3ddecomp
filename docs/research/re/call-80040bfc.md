# Call at 0x80040bfc

No traced entry reaches this address. `sra` shifts `a1` right by 10. `addiu` adds 1. `sll` shifts that left by 8. `sra` shifts `a0` right by 10. `addu` adds the two pieces. `lw` reads the word at `0x800a023c`. That word is not stated. `sll` shifts the sum left by 1 and adds the loaded word. `lhu` reads the halfword at that address. `a0` and `a1` are not stated, so the halfword is not stated. `srl` shifts it right by 12. `jr` returns. The delay slot sets `v0` to 1 when that field is not 0, and to 0 when it is. The arriving `ra` is not stated.

The 56 bytes from `0x80040bfc` through `0x80040c30` occur once.

## Our code

`call_80040bfc` keeps the index and the final 0 or 1. The host check uses `a0` 0, `a1` 0, and two halfwords.

## Gap

The word at `0x800a023c` is not stated. `a0`, `a1`, and `ra` are not stated.
