# Call at 0x8005bdd0

`CdDataCallback` in `0x8005bf80` is given this address. This boot does not reach that call.

`lw` reads `0x800d89c4`. [call-8005be3c.md](call-8005be3c.md) leaves that word 0 on this boot. `beq` at `0x8005bddc` takes `0x8005bdec`. The `jalr` is not this path.

The epilogue reloads `ra`. This note does not state the arriving value. `v0` stays 0. `jr ra` returns 0.

The 44 bytes from `0x8005bdd0` through `0x8005bdf8` occur once.

## Our code

`call_8005bdd0` returns 0 when the slot is 0. The host check expects 0.

## Gap

The arriving `ra` is not stated. This boot does not reach `0x8005bdd0`.
