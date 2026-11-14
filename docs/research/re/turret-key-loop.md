# Turret key loop

`call-800235ec.md` stops at `strcpy`. This note starts at the return address `0x80023628`. `s0` is 0. `s2` is `0x8009f548`. `s3` is `0x8009f614`. `s4` is `0x8009f548`. `s6` is 0. `sp` is `0x80010b44`.

`lw` loads the word at `0x8009f548`, which is `0x800bf450`. Those bytes are `Easy` and a zero byte. `jal` at `0x8002362c` targets `strcat`. `a0` is `0x80010b54`. `ra` is `0x80023634`. This note does not enter `strcat`.

`addiu` at `0x80023634` sets `a0` to `0x80010b54`. `addiu` at `0x80023638` sets `a1` to `sp` plus `0x7c`, which is `0x80010bc0`. That pointer is not zero. No earlier note stores the word at `0x7c(sp)`. `jal` at `0x8002363c` targets `0x80063ed8`. The delay is `sll s1, s0, 2`. `s0` is 0, so `s1` becomes 0. `ra` is `0x80023644`. The body is [call-80063ed8-13.md](call-80063ed8-13.md). The nonzero path stores 0 through `a1`, so the word at `0x80010bc0` becomes 0. The words at `0x800dd6e8` and `0x800dd6ec` stay 0, so `v0` returns 0. This note does not enter that body again.

`beq v0, zero, 0x8002365c` is taken. The store at `0x80023658` does not run. `s2` becomes `0x8009f54c` and `s0` becomes 1. The same three steps repeat for `Normal` and `Hard`. Both sides of the `beq` then add 4 to `s2` and 1 to `s0`, so the inner count does not depend on `v0`. When `s0` is 3, `beq` at `0x80023614` is taken. `s3` adds 8 and `s6` adds 1.

`s6` runs from 0 through `0x3e`. That is `0x3f` prefixes. The first word of each pair starts at `0x8009f614` and steps by 8. The first is `TurretMinBurst`. The last, at `0x8009f804`, is `SargeVehicleAutoaimVert`. The suffix base stays `0x8009f548`. Each call returns 0 for the same reason, and the store at `0x80023658` stays skipped. The taken path does not write the count words.

When `s6` is `0x3f`, `slti` at `0x80023600` yields 0. `beq` at `0x80023604` is taken. The delay sets `s0` to 0. The next address is `0x80023674`. `s2` is `0x8009f554`. `s3` is `0x8009f614` plus `0x3f` times 8, which is `0x8009f80c`. `s4` is `0x8009f548`. `s6` is `0x3f`.

## Our code

No source file is added. The remaining laps are the same taken compare.

## Gap

The next note is `call-80023674.md`. `s0` is 0. `s6` is `0x3f`.
