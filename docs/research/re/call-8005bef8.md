# Call at 0x8005bef8

[call-80074bd4.md](call-80074bd4.md) calls here. `ra` is `0x80074c50`. This boot does not reach that `jal`.

`v1` is `0x800d89b8`. `lw` at `0x8005bf14` reads `0x800d89bc`. [call-8005be9c.md](call-8005be9c.md) leaves that word 0 on this boot. Bit 1 is clear. `beq` at `0x8005bf20` takes `0x8005bf68`. The delay sets `s2` to 2. The `jal` of `0x80081a00` is not this path.

The epilogue reloads `ra`. `v0` stays 0. `jr ra` returns 0.

The 136 bytes from `0x8005bef8` through `0x8005bf7c` occur once.

## Our code

`call_8005bef8` returns 0 when bit 1 of the word is clear. The host check expects 0.

## Gap

The other side calls `0x80081a00`. No `tools/sdk_names.txt` line names that target. This boot does not take that side.
