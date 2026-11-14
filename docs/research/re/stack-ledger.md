# Stack from the entry to 0x8002390c

`entry.md` sets `sp` to `0x80010c64` at `0x8007fa00`. The entry notes from `entry-return.md` through `entry-after-third-compare.md` do not write `sp`. `entry-loop.md` returns from `0x8007faf8` with a `nop` delay. `entry-byte-compare.md` returns from `0x8007fb1c` with an `xori` delay. A re-check of `0x8007fa2c` through `0x8007fae8` shows no `sp` operand. `sp` on entry to `0x800251f8` is `0x80010c64`.

`call-800251f8.md` subtracts `0x50`. `sp` becomes `0x80010c14`. That frame stays open through `call-80025564.md`. Its saved `ra` stays `0x8007faec`.

These calls return to that frame with the same `sp`. Each line is the open and the traced close.

- `0x8007faf0` is `jr ra` with a `nop` delay in `call-8007faf0.md`.
- `0x8007f920` returns at `0x8007f9a0` with a `nop` delay in `call-8007f9a0.md`.
- `0x8007a628` subtracts `0x20`. `call-8007a604.md` adds `0x28` for the nested frame at `0x8007a540`, then `call-800252ac.md` adds `0x20`.
- `0x8007c334` returns with a `nop` delay in `call-8007c334.md`.
- `0x80076254` subtracts `0x18`. `call-80076264.md` adds `0x18`.
- `0x80075fdc` subtracts `0x18`. `call-80076010.md` adds `0x18`.
- `0x800760e8` does not write `sp` on the return to `0x80025380` and `0x80025388`.
- `0x800763e8` subtracts `0x20` in `call-800763e0.md`. `call-8007641c-second.md` releases that frame at `0x80076444`. The delay is `addiu sp, sp, 0x20`.
- `0x80076234` subtracts `0x18`. `call-80076234.md` adds `0x18`.
- `0x8007c03c` subtracts `0x18`. `call-8007c03c.md` adds `0x18`.
- `0x8007e130` subtracts `0x18`. `call-8007e130.md` adds `0x18`.
- `0x8007e150` subtracts `0x18`. `call-8007e150.md` adds `0x18`.
- `0x8007e17c` returns with a store delay in `call-8007e17c.md`. It does not write `sp`.
- `0x8007e1d8` subtracts `0x18`. `call-8007e1f8.md` adds `0x18`.
- `0x8007e118` returns with a `nop` delay in `call-8007e118.md`.
- `0x80060aac` subtracts `0x18`. `call-80060b3c.md` adds `0x18`.
- `0x8007d3f8` returns with a store delay in `call-8007d3f8.md`. It does not write `sp`.
- `0x80064588` subtracts `0x18`. `call-80064598.md` adds `0x18`. The nested `0x18` frames at `0x80094f54` and `0x80095744` are closed in `call-80094f64.md` and `call-800957e4.md`.
- `0x800621dc` subtracts `0x28`. `call-80062238.md` adds `0x28`. The later entry does the same in `call-80062238-2.md`.
- `0x800636b8` subtracts `0x20`. `call-800636b8.md` adds `0x20`.
- `0x80077fdc` returns with a store delay in `call-80077fdc.md`. It does not write `sp`.
- `0x8007d12c` subtracts `0x18`. `call-8007d12c.md` and `call-8007d12c-2.md` add `0x18`.
- `0x80063668` subtracts `0x60`. `call-80063684.md` adds `0x60`.
- `0x8001d590` subtracts `0x70`. `call-8001d590.md` adds `0x70`.

`call-80025564.md` takes `beq v0, zero, 0x800255d0`. The calls from `0x8002556c` through `0x800255bc` are not this boot. `sp` at the `jal` to `0x80023848` is `0x80010c14`.

`call-80023848-2.md` subtracts `0x18`. `sp` becomes `0x80010bfc`. The branches skip the calls at `0x80023864`, `0x80023880`, and `0x800238e8`. The taken call is `0x80023794` at `0x80023904`. `call-80023794-2.md` subtracts `0x28`. `sp` becomes `0x80010bd4`.

`call-80063b34.md` and `call-80063b34-2.md` subtract `0x88` and `call-80063ed4.md` adds `0x88` before `0x800237d0`. `call-80063b34-3.md` subtracts `0x88` again. `sp` becomes `0x80010b4c`. `call-80062434.md` subtracts `0x40`, and `call-80062434-4.md` is that entry. `sp` at its `jal` is `0x80010b0c`.

The `jal` at `0x8002390c` is after `addiu sp, sp, 0x28` at `0x80023844`. Reaching it also requires the `0x40` and `0x88` pops already traced for the earlier entries. After those three adds, the open frames are `0x800251f8` and `0x80023848`. `sp` at `0x8002390c` is `0x80010bfc`. This boot is still at `call-80062434-4.md`, so it has not executed that `jal`.

`call-80022f1c.md` subtracts `0xb8` from the arrival `sp`. The arrival value is `0x80010bfc`, so `sp` inside that function is `0x80010b44`. `a1` at `0x800235b0` is that `sp` plus `0x78`, which is `0x80010bbc`. It is not zero.

The same `a1` computed from the still-open `0x80010b0c`, without the three pops, is `0x80010acc`. That is also not zero. It is not the `sp` at `0x8002390c`.

`call-80023674.md` is the epilogue of that `0x80022f1c` frame on the stated `sp`. It adds `0xb8`. `sp` returns to `0x80010bfc`. The mission frames at `call-80062434-4.md` stay open. This return does not pop them.

`call-80023914.md` adds `0x18`. `sp` is `0x80010c14`. The frame at `0x80023848` closes. The frame at `0x800251f8` stays open. Its saved `ra` stays `0x8007faec`.

`call-800255d8.md` calls `0x80045374` at that `sp`. `call-80045374.md` subtracts `0xd0`. `sp` is `0x80010b44`. That frame stays open. Its saved `ra` is `0x800255e4`.

`call-80045570.md` is the epilogue of that frame on the forward lane from `0x80045418`. It adds `0xd0`. `sp` is `0x80010c14`. The frame at `0x80045374` closes. The frame at `0x800251f8` stays open. Its saved `ra` stays `0x8007faec`. The static boot does not take `beq` at `0x800453c4`. This close is the forward lane.

`call-80065894.md` subtracts `0x30` at that `sp`. `sp` is `0x80010be4`. That frame stays open. Its saved `ra` is `0x800255ec`.

`call-80063ed8-17.md` subtracts `0x38` from that frame. `sp` is `0x80010bac`. That frame stays open at `call-80076508-17.md`. Its saved `ra` is `0x8006591c`.
