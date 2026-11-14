# Call at 0x8007ac2c

No traced entry reaches this address. The prologue subtracts `0x18` from `sp` and copies `a0` into `v0`. `andi` keeps the low 16 bits of `a1`. `srl` shifts that right by 4. That value is the `a0` of the call. `sw` saves `ra`. `jal` at `0x8007ac40` targets `0x8008cf6c` and sets `ra` to `0x8007ac48`. The delay slot copies the saved `a0` into `a1`. `tools/sdk_names.txt` names `0x8008cf6c` `RotMatrixX`. This note does not enter it. `RotMatrixX` does not state `v0`. The epilogue does not read `v0`.

`lw` restores `ra`. `jr` returns. The delay slot adds `0x18` to `sp`. The restored `ra` is the arriving `ra`, which is not stated. The arriving `a0` and `a1` are not stated.

The 44 bytes from `0x8007ac2c` through `0x8007ac54` occur once.

## Our code

`call_8007ac2c` does not enter `RotMatrixX`. The host check calls it.

## Gap

`RotMatrixX` does not state `v0`. The arriving `a0`, `a1`, and `ra` are not stated.
