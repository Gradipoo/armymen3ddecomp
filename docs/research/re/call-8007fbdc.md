# Call at 0x8007fbdc

No traced entry reaches this address. `t2` is `0xb0`. `t1` is 8. `jr` at `0x8007fbe0` jumps to `0xb0`. [bios.md](bios.md) says a B function is called at `0xb0` with the number in `t1`. The table does not name number 8. This note does not enter that body. The delay sets `t1` to 8. `v0` is not written here. The arriving `ra` stays the return for that B function.

The 12 bytes from `0x8007fbdc` through `0x8007fbe4` occur once.

## Our code

`call_8007fbdc` stops at the jump. The host check only calls the function.

## Gap

The B function number 8 is not named in [bios.md](bios.md).
