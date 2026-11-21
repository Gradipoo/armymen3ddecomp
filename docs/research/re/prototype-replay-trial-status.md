# PROTOTYPE row 4 SOTN-style replay trial status

Status: **not started** as a full replay harness in this repository. A
deterministic PAD spawn fixture and a fixed eight-frame movement script are
partial stand-ins only. They do not record controller frames, replay
frame-indexed input, or run drift checks.

Method and revision pin: [PROTOTYPE.md](../../PROTOTYPE.md), section **SOTN:
native entry and repeatable input**. Do not copy the upstream save format,
game state layout, or reconstructed gameplay.

## Row 4 acceptance checklist

Adapt SOTN's replay pattern to Army Men using only state our notes support.
Each item must pass before row 4 counts as done. All items remain unchecked.

- [ ] Frame-indexed controller input record and playback on a native run.
- [ ] Initial replay start state captured and restored (fields cited in notes).
- [ ] Small set of Army Men state checks at named frames or checkpoints.
- [ ] Drift check: repeated replay with the same inputs compares state; drift
      is reported when checks disagree.

## Partial stand-ins (not a full replay)

| Stand-in | Role | Limit |
| --- | --- | --- |
| `alp1_pad_spawn`, `alp1_pad_spawn_retail` | Golden spawn from fixture or owner `ALP1.PAD` | Bytes and `(x, z, heading)` only; no frame tape |
| `prototype_task_8` eight-frame script | Fixed `MissionPadScript` in tests | Host movement slice, not retail pad replay |
| [alp1-pad-spawn.md](alp1-pad-spawn.md) | Parser and disc-free fixture cite | Spawn decode, not input history |

See [prototype-task-8.md](prototype-task-8.md) for the synthetic row 8 acceptance
script. See [prototype-alp1-movement-observation.md](prototype-alp1-movement-observation.md)
for the PCSX-Redux operator procedure to capture retail movement evidence
under `build/coordination/`. That procedure does not close this checklist until
a replay harness ties observation inputs to native drift checks.

## Execution state in this repo

No `replay.c`-style module, no frame tape format, and no drift runner exist in
tree. Row 3 (PsyZ adapter) and rows 5 through 9 remain independent milestones.
Captured GPU packet replay or menu frame replay alone does not pass rows 7 or
9 per [PROTOTYPE.md](../../PROTOTYPE.md).

## Stop rules

Stop after **three failures at the same problem**. Record what was tried, what
was learned, and the next bounded outcome. Do not copy SOTN's save format or
widen state checks beyond cited note offsets without a new research note.