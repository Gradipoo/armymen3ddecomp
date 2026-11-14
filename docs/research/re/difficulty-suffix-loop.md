# Difficulty suffix loop

`call-80063f18-13.md` returns to `0x800235bc` with `v0` 0, `s0` 1, `s1` `0x8009f54c`, `s2` and `s3` `0x8009f554`, `s4` `0x8009f548`, and `s6` 0. `s7` is `0x8009f820`. `sp` is `0x80010b44` in [stack-ledger.md](stack-ledger.md).

`beq v0, zero, 0x800235d4` is taken. `s1` becomes `0x8009f550`. The jump delay leaves `s0` as 2. The word at `0x8009f550` is `0x800bf460`, the bytes `Hard` and a zero. `s0` is still below 3, so that body runs, then `s0` becomes 3. `beq` at `0x80023590` is taken. `s2` becomes `0x8009f55c` and `s6` becomes 1.

Each later body is the same control. `s6` runs from 1 through 23. For each value, `s0` runs 0, 1, and 2. The three suffix words stay `0x800bf450`, `0x800bf458`, and `0x800bf460`. The prefix word is the first word of the pair at `s2`. Those 24 pairs, from `0x8009f554` in steps of 8, point at these strings:

`SargeHP`, `SargeMaxHP`, `RiflemanHP`, `GrenadierHP`, `BazookamanHP`, `FlameThrowermanHP`, `MortarmanHP`, `EngineermanHP`, `MineSweepermanHP`, `TurretmanHP`, `FortressHP`, `JeepHP`, `JeepArmor`, `TankHP`, `TankArmor`, `HalftrackHP`, `HalftrackArmor`, `TruckHP`, `TruckArmor`, `TrainHP`, `TrainArmor`, `MedPackHP`, `MedKitHP`, `TerrainHP`.

The second word of each pair is the store destination. `beq` at `0x800235bc` is taken while `v0` is 0, so the store at `0x800235c4` does not run. `call-80063ed8-13.md` returns 0 when the words at `0x800dd6e8` and `0x800dd6ec` are 0, and that taken side does not store those words. `strcpy` and `strcat` do not store them either. Each remaining call returns 0. This note does not enter those bodies again.

When `s6` is `0x18`, `slti` at `0x80023578` yields 0. `beq` at `0x8002357c` is taken. The delay sets `s0` to 0. Control is at `0x800235ec`. `s6` is `0x18` on arrival. `s2` is `0x8009f554` plus `0x18` times 8, which is `0x800a0014`. `s3` stays the last pair, `0x800a000c`. `s1` is `0x8009f554`. `s4` is `0x8009f548`. The word at `0x80010bbc` stays 0.

## Our code

No source file is added. The remaining laps are the same taken compare.

## Gap

The next note is `call-800235ec.md`. `s0` is 0. `s6` is `0x18` until that note's first instruction.
