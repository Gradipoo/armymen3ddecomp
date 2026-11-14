# Call at 0x8005eeb4

No traced entry reaches this address. The prologue saves `ra`. `jal` at `0x8005eebc` targets `0x8006658c` and sets `ra` to `0x8005eec4`. The delay slot is `nop`. [call-8006658c.md](call-8006658c.md) names that target. `a0` stays the arriving value, which is not stated. This note does not enter the body. The epilogue does not read `v0`.

`lw` restores `ra`. `jr` returns through it. The delay slot adds `0x18` to `sp`. The restored `ra` is the arriving `ra`, which is not stated.

The 32 bytes from `0x8005eeb4` through `0x8005eed0` occur once.

## Our code

`call_8005eeb4` does not enter `0x8006658c`. The host check calls it.

## Gap

The arriving `a0` and `ra` are not stated.
