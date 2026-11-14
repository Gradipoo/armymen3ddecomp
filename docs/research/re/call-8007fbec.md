# Call at 0x8007fbec

No traced entry reaches this address. `t2` is `0xb0`. `t1` is `0xc`. `jr` jumps to `0xb0`. [bios.md](bios.md) says an B function is called there with the number in `t1`. The table does not name `0xc`. This note does not enter that body. The delay sets `t1`. `v0` is not written here.

The 12 bytes from `0x8007fbec` through `0x8007fbf4` occur once.

## Our code

`call_8007fbec` stops at the jump. The host check only calls the function.

## Gap

The B function `0xc` is not named in [bios.md](bios.md).
