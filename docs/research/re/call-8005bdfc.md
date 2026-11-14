# Call at 0x8005bdfc

`CdReadyCallback` in `0x8005bf80` is given this address. This boot does not reach that call.

`lw` reads `0x800d89c8`. [call-8005be50.md](call-8005be50.md) leaves that word 0 on this boot. `beq` at `0x8005be08` takes `0x8005be18`. The `jalr` is not this path. The delay would keep the low byte of `a0`. That byte is not stated.

The epilogue reloads `ra`. This note does not state the arriving value. `v0` stays 0. `jr ra` returns 0.

The 44 bytes from `0x8005bdfc` through `0x8005be24` occur once.

## Our code

`call_8005bdfc` returns 0 when the slot is 0. The host check expects 0.

## Gap

The arriving `ra` is not stated. This boot does not reach `0x8005bdfc`.
