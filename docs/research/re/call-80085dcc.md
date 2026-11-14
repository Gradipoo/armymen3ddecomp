# Call at 0x80085dcc

No traced entry reaches this address. `t2` is `0xb0`. `t1` is `0x19`. `jr` jumps to `0xb0`. [bios.md](bios.md) says an B function is called there with the number in `t1`. The table does not name `0x19`. This note does not enter that body.

The 12 bytes from `0x80085dcc` through `0x80085dd4` occur once.

## Our code

`call_80085dcc` stops at the jump. The host check only calls the function.

## Gap

The B function `0x19` is not named in [bios.md](bios.md).
