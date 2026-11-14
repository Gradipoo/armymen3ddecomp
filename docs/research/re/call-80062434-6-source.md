# Source of the sixth call at 0x80062434

`call-80062434-6.md` calls `strcpy` with `a1` 0 and then calls `0x80061f80` with `a0` 0. This note lists the stores that are still missing. It does not take `beq` at `0x80061fe4`.

`call-8006596c.md` loads `a0` from `0x800ddb38` and calls `0x80062e0c` with `a1` `0x800ddc08` and `a2` `0xe00`. `call-80065954.md` stored the `Backup_IconFile` return at `0x800ddb38`. `call-80063f18-18.md` returned 0 because the words at `0x800dd6e8` and `0x800dd6ec` are still 0. So the arrival `a0` of `0x80062e0c` is 0.

`call-80062e0c.md` copies that 0 into `v0`. The delay of `jal` `0x80062434` copies `v0` into `a1`. That is why `strcpy` has `a1` 0. The same span sets `a0` to `sp` plus `0x10`, which is `0x80010b8c`. That address is the pointer passed onward. It is not the `strcpy` source.

[entry-after-fill.md](entry-after-fill.md) writes 0 from `0x800c5458` through the last word before `0x800e44e0`. That range includes `0x800dd6e8`, `0x800dd6ec`, `0x800ddb38`, and `0x800ddc08`. It does not include `0x80010b8c` or address 0. No traced store writes `0x80010b8c` before the call. `call-8006591c.md` copies `bk0:` to `0x800ddbe8` and calls `strcat` with `a1` 0. That note does not state a store at `0x800ddc08`.

The missing values are:

- The byte at address 0. [call-00000000.md](call-00000000.md) says it is outside the text image. No traced store writes it. This byte is what `beq` at `0x80061fe4` compares.
- The bytes at `0x800dd668` after this `strcpy`. `a1` is 0, so `call-80062434-6.md` does not state them.
- The bytes at `0x80010b8c`. The zero fill does not cover that stack slot, and no traced store writes it. The traced load does not use those bytes.
- A store at `0x800ddc08` after the zero fill. None is traced. The traced load does not use those bytes.

`docs/research/re/deviations.md` has no lane for this branch.
