# Call at 0x8005be9c

[call-80074278.md](call-80074278.md) calls here. `a0` is 0. `ra` is `0x80074298`. This boot does not reach this address.

`lui` and `addiu` set `a0` to `0x8005be64`. `jal` at `0x8005bea8` targets `0x8005be28`. [call-8005be28.md](call-8005be28.md) names that body. On this side the word at `0x800d89c0` is still 0, so that call returns 0 and stores `0x8005be64`. `ra` for that call is `0x8005beb0`. This note does not enter that body.

`a0` becomes 9. `a1` becomes 0. `a2` becomes 0. `lw` at `0x8005bec0` loads `0x800d89bc`. That address is inside the zero fill in [entry-after-fill.md](entry-after-fill.md). No traced note stores it before this instruction, so the word is 0. `ori` with 2 makes 2. `sw` stores 2 at `0x800d89bc`. This boot does not run that store.

`jal` at `0x8005bed0` targets `0x80081a68`. `tools/sdk_names.txt` names that target `CdControl`. `a0` is 9. `a1` is 0. `a2` is 0. `ra` is `0x8005bed8`. The delay is `nop`. This note does not enter that body. `v0` on return is not stated, so `bne` at `0x8005bed8` is not followed.

The 60 bytes from `0x8005be9c` through `0x8005bed4` occur once.

## Our code

`call_8005be9c` stores the pointer through `call_8005be28`, then sets bit 1 of the slot. It does not call `CdControl`. The host check sees the slot become 2.

## Gap

`CdControl` at `0x80081a68` returns to `0x8005bed8`. `v0` is not stated. This boot does not reach `0x8005be9c`.
