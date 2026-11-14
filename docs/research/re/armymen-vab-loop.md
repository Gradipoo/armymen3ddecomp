# VAB path loop at 0x800453c0

`armymen-vab-open.md` returns to `0x800453d8` with `v0` 0 and closes the `0x80062434` frame. `s2` becomes 0. `bne` at `0x800453dc` is not taken. `0x8007d234` returns 0. `beq` at `0x800453f4` is taken. `beq` at `0x80045410` is taken. The delay leaves `v0` as `s1` minus `s3`, which is 0. Control is at `0x800453c0`. `s1` is 0. `s3` is 0. `sp` is `0x80010b44`.

`s3` is the 0 copied from the first `0x8007d234` return in `call-800453a8.md`. The instructions from `0x800453c0` back to that same address do not write `s3`. `s1` is replaced by the next `0x8007d234` return. With `a0` 2, that return is the word at `0x800e196c`.

Both words sit in the zero fill from `entry-after-fill.md`. `call-8007d12c-2.md` stored 0 at `0x800e1968`, the previous word. No traced store writes `0x800e196c`. The taken branch in `call-8007d234.md` does not write it, so the word stays 0 and `s1` stays 0. `deviations.md` lists the stores of `0x800e152c`. None of those addresses is in this lap. `call-80075198-11.md` loads that word, takes `beq` at `0x800751d0`, and returns 0. The lap does not store it. `0x80062434` then returns 0, so `s2` stays 0.

`sltiu` at `0x800453c0` compares `s1` minus `s3` with `0x3a98`. The difference is 0, so `v0` becomes 1. `beq v0, zero, 0x80045418` is not taken. The body calls `0x80062434` again with the same `a0` and `a1` as `call-800453a8.md`. That call returns 0. `bne s2, zero, 0x80045420` is not taken. `0x8007d234` returns 0 again. The two compares send control back to `0x800453c0`.

The loop reaches `0x80045418` only when `beq` at `0x800453c4` is taken. That is when `v0` is 0, which is when the unsigned difference `s1` minus `s3` is not below `0x3a98`. `s3` stays 0 and `s1` stays 0 while `0x800e196c` stays 0, so the difference stays below `0x3a98`. This boot does not reach `0x80045418`. No exit note is written. The instructions at `0x80045418` are not traced.

The frame at `0x80045374` stays open. Its saved `ra` stays `0x800255e4`. The frame at `0x800251f8` stays open. Its saved `ra` stays `0x8007faec`. Each traced lap closes the `0x80062434` frame before the branch back.
