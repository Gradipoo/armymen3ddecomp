# Call at 0x8005c0fc

No traced entry reaches this address. `a0` is 5.

`jal` at `0x8005c104` targets `0x8005c058`. [call-8005c058.md](call-8005c058.md) names that body. `ra` is `0x8005c10c`. The delay sets `a0`. That body stops at unnamed `0x800818cc`. `v0` is not stated. This note does not enter that body again.

The epilogue reloads `ra`. This note does not state the arriving value. `jr ra` leaves `v0` unstated.

The 32 bytes from `0x8005c0fc` through `0x8005c118` occur once.

## Our code

`call_8005c0fc` calls `call_8005c058` with 5. The host check only calls the function.

## Gap

`v0` from `0x8005c058` is not stated. The arriving `ra` is not stated.
