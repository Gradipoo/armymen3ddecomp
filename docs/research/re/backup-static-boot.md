# Static boot parked at 0x80061fe4

The forward lane from `0x80045418` is parked at `beq` `0x80061fe4` in [call-80061f80-6.md](call-80061f80-6.md). This note does not take a side.

`lb` there reads the byte at address 0. [call-00000000.md](call-00000000.md) records that address 0 is outside the text image `0x80010000` through `0x800c57ff`. No traced store writes it. [entry-after-fill.md](entry-after-fill.md) starts at `0x800c5458`. Retail play has to provide that byte before the compare can be followed. `tolower` does not choose the side. The delay stores `v0`.

[backup-count-words.md](backup-count-words.md) finds one store that adds 1 to `0x800dd6e8`, at `0x80063e20`. The traced entries of `0x80063b34` take `beq` at `0x80063b78` and do not reach it. The words at `0x800dd6e8` and `0x800dd6ec` stay 0, so each `Backup_*` lookup returns 0. [call-80062434-6-source.md](call-80062434-6-source.md) records the `strcpy` source 0 that follows.

The open frames stay the frames in `call-80061f80-6.md`. `sp` is `0x80010aec`. The saved `ra` values stay `0x80062474`, `0x80062e34`, `0x80065998`, `0x800255ec`, and `0x8007faec`.

`docs/research/re/deviations.md` pauses this forward lane. A later note does not start past `0x80061fe4` until the byte at address 0 is stated from a traced store, or Sean opens a new lane.
