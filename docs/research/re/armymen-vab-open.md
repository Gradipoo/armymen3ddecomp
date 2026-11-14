# ARMYMEN.VAB open

`call-800624cc-4.md` stops at `jalr` `0x80075198`. That body is [call-80075198-11.md](call-80075198-11.md). The word at `0x800e152c` is still 0, so `v0` returns 0 to `0x80062514`. `bne` at `0x80062514` is not taken. The delay stores 0 at `0x80010bbc`. `a1` is 0. `a2` is `0x800ae5f0`. `a0` is 5. The shift is 0, so the next `jalr` is `0x80075198` again. The delay sets `a3` to 0. `ra` is `0x80062548`. That call returns 0 for the same reason. This note does not enter either body.

`beq` at `0x80062548` is taken. The delay stores 0 at `0x80010bbc`. `s3` is still 0, so `v0` becomes 0. The epilogue restores `ra` to `0x800453d8`, `s3` to 0, `s2` to 0, `s1` to 0, and `s0` to `0x80080000`. `jr ra` returns to `0x800453d8`. The delay adds `0x40` to `sp`. `sp` is `0x80010b44`. The frame at `0x80062434` closes.

`s2` becomes 0. `bne` at `0x800453dc` is not taken. `jal` at `0x800453e4` calls `0x8007d234` with `a0` 2. [call-8007d234.md](call-8007d234.md) returns 0, and this path does not store `0x800e196c`. `v1` and `s1` are both 0, so `beq` at `0x800453f4` is taken. `s2` is 0, so `beq` at `0x80045410` is taken. The delay leaves `v0` as 0. `sltiu` at `0x800453c0` yields 1. `beq` at `0x800453c4` is not taken.

The next `jal` is `0x80062434` with the same `a0` and `a1` as [call-800453a8.md](call-800453a8.md). The lap returns 0 again while `0x800e152c` stays 0 and `0x8007d234` stays 0. `s1` and `s3` stay 0, so `s1` minus `s3` stays below `0x3a98`. The exit at `0x80045418` is not this boot. The `break` at `0x8004540c` is not this boot.

The frame at `0x80045374` stays open. Its saved `ra` stays `0x800255e4`. The frame at `0x800251f8` stays open. Its saved `ra` stays `0x8007faec`.

## Our code

No source file is added. The remaining laps are the same taken compares.

## Gap

Control is back at `0x800453c0`. `s1` is 0. `s3` is 0. `s2` is 0. `sp` is `0x80010b44`. The next lap is not a new note.
