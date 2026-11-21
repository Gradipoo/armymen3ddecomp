# PROTOTYPE task 1 retail screen observation record

Status: **partial**. Scattered notes and local captures exist. This file is the
row 1 acceptance index. It does not pass the full [PROTOTYPE.md](../../PROTOTYPE.md)
table check yet. It does not claim a native running screen or parity with the
parked static-boot spine.

## Row 1 acceptance (from roadmap table)

Define the first screen from retail observation using the PCSX-Redux capture
setup. Record:

| Requirement | Where it lives | Recorded? |
| --- | --- | --- |
| Executable identity | Local extract under owner machine; run log names disc EXE | Partial: named in [first-screen-observation.md](first-screen-observation.md); not re-verified every run |
| Emulator identity | PCSX-Redux dev build 443, version `7637751d`, BIOS `8d8cb7e4` (SCPH-7003 US) | Yes: [first-screen-observation.md](first-screen-observation.md) |
| Boot mode | Interpreter, fast boot disabled for menu path | Yes: same note |
| Memory-card state | Two task-local cards created and loaded; repeat used preserved initial copies; both slots inserted, pad 1 connected | Partial: config described; guest card contents and numeric pad type not verified |
| Exact controller steps | Return 200 ms during intro; Down 100 ms at `1 PLAYER` menu | Yes for clean run 5; guest input edges not traced |
| Observed path (no invented static-boot state) | Retail MEMCARD lane, not the parked `beq` at `0x80061fe4` | Yes: cite [deviations.md](deviations.md) Retail MEMCARD backup path; do not use static-boot backup-count 0 as retail fact |
| One displayed frame | Stable `1 PLAYER` with `NEW GAME` selected | Yes: run 5 frame 3720 (`menu-before.png`) |
| Asset reads for that frame | FRONT.TIM upload lead; sector 16 metadata read | Partial: `MEMCARD.TIM` lookup and eight CD wrapper pairs; menu FRONT open path on row 2 |
| GPU submission for that frame | Bounded `LoadImage` / `DrawOTag` counts | Partial: runs 8–11; not a full stable-menu packet inventory |
| Controller-driven transition | Down moves highlight `NEW GAME` → `OPTIONS` | Yes: run 5 before/after PNGs; not pixel-exact |

Captures and traces stay under `build/`. They are not in git.

## Linked records

There is no separate `screen-retail-observation` note. Use these instead:

| Topic | Link |
| --- | --- |
| Detailed run log (runs 5–11) | [first-screen-observation.md](first-screen-observation.md) |
| Local evidence tree | `build/coordination/retail-screen/` (owner machine) |
| PCSX-Redux install, portable config, Lua capture | [tools/pcsx/README.md](../../../tools/pcsx/README.md) |
| Retail path split (menu vs bootcamp vs ALP1) | [prototype-retail-paths.md](prototype-retail-paths.md) |
| Mission observation after NEW GAME (row 8; not the menu row) | [prototype-alp1-movement-observation.md](prototype-alp1-movement-observation.md) |
| Host window / disc-free smoke (not retail recreation) | [PLATFORM.md](../../PLATFORM.md) |
| Retail vs static boot MEMCARD path | [deviations.md](deviations.md) § Retail MEMCARD backup path |
| Row 2 service inventory | [prototype-task-2.md](prototype-task-2.md) |

## Boot path honesty

Retail play on the owner machine enters `0x80062e0c` once with `a0` pointing
at `MEMCARD.TIM` and keeps `0x800dd6e8` nonzero. The static boot lane at
`0x80061fe4` stays deviation-parked with count words at 0
([deviations.md](deviations.md), [backup-static-boot.md](backup-static-boot.md)).
Row 1 evidence comes from PCSX-Redux retail runs only. Do not continue the
static spine to fake menu state.

## Row 1 completion checklist

- [ ] Executable hash or cited `exe_info` identity in one row-1 table row, refreshed against the current disc image
- [ ] Memory-card guest state verified (both slots, saves, and effective pad type) in a new capture note
- [ ] Guest input edges tied to frame numbers or a PCSX input trace (host key timings alone are insufficient)
- [ ] Stable-menu asset read that names FRONT.TIM (or cites open failure) at a named frame checkpoint
- [ ] Stable-menu GPU sample (not exit-animation run 11 only) tied to the same checkpoint
- [ ] Filled ALP1-style observation checklist for a dedicated row-1 rerun (`alp1_observation_checklist.py` is row 8 only today; row 1 has no validated checklist run)
- [ ] Live address cite at the Down transition (pad dispatch word at `0x800c3ea4` with `s2` change)
- [ ] Pixel capture accepted for row 7 checkpoint naming ([prototype-task-7-pixel-checkpoint.md](prototype-task-7-pixel-checkpoint.md); run 5 BMPs exist locally, repo has no pixels)

## Tier verdict

**Observation tier, incomplete.** Partial documentation exists across
[first-screen-observation.md](first-screen-observation.md), local
`build/coordination/retail-screen/`, and [prototype-task-2.md](prototype-task-2.md).
Before this note, there was no single consolidated row 1 acceptance artifact.
This file indexes what is recorded and what is still open. Close items in the
checklist in follow-up observation work, not by inferring static-boot state.