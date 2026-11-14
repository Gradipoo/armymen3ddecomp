# Count words at 0x800dd6e8 and 0x800dd6ec

`call-80063f18.md` loads these two words. `0x800dd6e8` is the count. `0x800dd6ec` is the next word. `s5` is 0. `sltu` of 0 and the count is 0 when the count is 0, so `beq` at `0x80063f30` is taken and `v0` becomes 0. The `Backup_Region`, `Backup_Product`, `Backup_Description`, `Backup_Name`, and `Backup_IconFile` entries take that side. [call-80062434-6-source.md](call-80062434-6-source.md) follows that 0 into `strcpy`.

[entry-after-fill.md](entry-after-fill.md) writes 0 from `0x800c5458` through the last word before `0x800e44e0`. Both words are in that range.

The text image has two stores through the offset `-0x2918`, and one store of the next word:

- `0x80063b08` sets `a0` to `0x800dd6e8` and `a1` to 0, then calls `0x8007f920` with `a2` `0xc`. That fills 12 bytes, so it writes 0 through `0x800dd6f0`. The executable word at `0x800b595c` is `0x80063b08`. No traced `jal` or `jalr` targets `0x80063b08`.
- `0x80063e20` is `sw v0, -0x2918(s6)` after `addiu v0, v0, 0x1`. `lui` at `0x80063c5c` has set `s6` to `0x800e0000`, so the store is `0x800dd6e8`. This is the store that adds 1 to the count. It is inside `0x80063b34`, after `0x80063c48`.
- `0x80063bf0` is `sw s4, 0x4(a0)` with `a0` equal to `0x800dd6e8`, so it writes `0x800dd6ec`. It runs only when `bne` at `0x80063bc8` is not taken and `bne` at `0x80063bd8` is not taken. Both of those compare a loaded word with 0. The count load is the first. A nonzero count skips this store. The store does not write `0x800dd6e8`.
- `0x80064110` sets `v0` to `0x800e0000` and `0x80064118` stores 0 at `0x800dd6e8`. The only `jal` is `0x80023864`. [call-80023848-2.md](call-80023848-2.md) loads `0x8009f818` as the executable word 0, so `beq` at `0x8002385c` is taken and this `jal` does not run.

No instruction uses the offset `-0x2914`. Nothing else stores `0x800dd6ec`.

[call-80063b78.md](call-80063b78.md) and [call-80063b78-2.md](call-80063b78-2.md) take `beq v0, zero, 0x80063ea4`. The body at `0x80063b80` is not those entries, so they do not reach `0x80063c5c` or `0x80063e20`. [mission-ini-loop.md](mission-ini-loop.md) and [difficulty-suffix-loop.md](difficulty-suffix-loop.md) record the same return of 0. The `Backup_*` calls enter `0x80063ed8` with `a1` 0, load the two words, and return 0. They do not store them.

The count stays 0 on this static boot. `beq` at `0x80063f30` stays taken. That does not state the byte at address 0, so `beq` at `0x80061fe4` stays unknown. [deviations.md](deviations.md) records retail boots that leave `0x800dd6e8` nonzero and enter `0x80062e0c` with `a0` `0x800e6cfc`. That path does not state this branch.
