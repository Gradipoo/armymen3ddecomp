# Call at 0x80073eec

No traced call enters here yet. The later call at `0x80074008` passes `a0` 0 and `a1` `0x800` once that caller is traced. `ra` for that call would be `0x80074010`.

`lw` at `0x80073ef0` loads `0x800e1534`. That address is inside the zero fill in [entry-after-fill.md](entry-after-fill.md). No traced note stores it, so it is 0. `addu` adds `a0` and `a1`. For `a0` 0 and `a1` `0x800` the sum is `0x800`. `sltu` against 0 is 0. `bne` at `0x80073efc` is not taken. `subu` subtracts 0. `jr ra` returns the sum. `v0` is `0x800` for those arguments.

The 36 bytes from `0x80073eec` through `0x80073f0c` occur once.

## Our code

`call_80073eec` returns the sum when the sum is not smaller than the limit, and the sum minus the limit when it is smaller. The host check uses 0, `0x800`, and limit 0.

## Gap

This boot does not reach `0x80073eec`. The next use is the call at `0x80074008`.
