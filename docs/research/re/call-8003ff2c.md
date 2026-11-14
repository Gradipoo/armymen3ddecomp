# Call at 0x8003ff2c

No traced entry reaches this address. The prologue subtracts `0x18` from `sp`. `addiu` writes `0x4c` into `a0`. `sw` saves `ra`. `jal` at `0x8003ff38` targets `0x8001b238` and sets `ra` to `0x8003ff40`. The delay slot saves `s0`. [call-8001b238.md](call-8001b238.md) names that target. This note does not enter it. The next instruction copies `v0` into `s0`. That note does not state `v0` on return, so the words after the delay slot are not traced.

The 20 bytes from `0x8003ff2c` through `0x8003ff3c` occur once.

## Our code

`call_8003ff2c` does not enter `0x8001b238`. The host check calls it.

## Gap

`0x8001b238` does not state `v0` on return.
