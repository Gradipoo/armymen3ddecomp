# PROTOTYPE task 8 synthetic acceptance

Status: **synthetic** met at this change; **disc-backed row 8** when owner
`ALP1.TXT` is present (`ctest prototype_task_8_retail`). Retail movement,
collision, camera, and gameplay comparison are deferred.

## Mission choice

**ALP1** (Alpine mission 1). Owner files live under `build/disc/DATA/`:
`ALP1.TXT` (header `//Alpine1 Mission1`), plus companion `.MAP`, `.PAD`,
`.MDL`, and related assets. This slice declares paths only. It does not
parse MAP, MDL, or TXT. Disc-free start state is the pad index 1 fixture in
`alp1_pad_spawn_fixture.hpp`. Retail paths load owner `ALP1.PAD` when present.

Load-path research (not executed here): [mission-ini-loop.md](mission-ini-loop.md)
and [call-80063b34.md](call-80063b34.md) cite `call_80063b34` on the
`\mission.ini` loop returning path GPR `0x800bfdbc`.

## Start state

Host stand-in in `MissionMovementStartState`:

| Field | Disc-free (`prototype_task_8`) | Retail path (pad index 1) |
| --- | --- | --- |
| `x` | `50` from the fixture bytes | `50` from [alp1-pad-spawn.md](alp1-pad-spawn.md) |
| `z` | `1252` from the fixture bytes | `1252` from owner `ALP1.PAD` |
| `heading` | `50` from the fixture bytes | `50` from owner `ALP1.PAD` |

## Fixed input script

Eight frames in `MissionPadScript` (`tests/test_prototype_task_8.cpp`):

| Frames | `s2` | Meaning |
| --- | --- | --- |
| 0–3 | `2` | Idle per [menu-scan-pad-sdl.md](menu-scan-pad-sdl.md) |
| 4–7 | `6` | Cross held; synthetic forward |

`run_mission_movement_frames` advances `z` by 16 per Cross frame.
`// gap:` collision, camera, and GTE are not applied.

## Checks

`ctest prototype_task_8` (disc-free):

- `record_mission_load_intent()` returns `mission_path_gpr == 0x800bfdbc`
- `frames_run == 8`
- `x` and `heading` unchanged; `z` increased
- `final_state` matches `state`

`ctest prototype_task_8_retail` when `build/disc/DATA/ALP1.TXT` exists:

- Opens TXT; first line contains `Alpine1`
- Same movement checks as synthetic (no retail position compare)

## Host API

| Piece | Path |
| --- | --- |
| Declaration paths | `components/exe/mission_movement_slice.hpp` |
| PAD spawn (index 1) | `components/exe/alp1_pad_spawn.hpp` |
| Frame runner | `components/exe/mission_movement_slice.cpp` |
| Menu load cite | `components/exe/mission_menu_handoff.hpp` |

## Remaining gaps (honest limits)

| Gap | Note |
| --- | --- |
| MAP / MDL collision | No geometry load or blocking |
| Camera | No mission camera chain |
| GTE / animation | No retail body update |
| Retail movement compare | Deferred; synthetic z step only |
| Mission gameplay | [prototype-alp1-movement-observation.md](prototype-alp1-movement-observation.md): USA **NEW GAME** may load **bootcamp** (no mission title; operator map guess), not verified `DATA/ALP1.*` play. |

Row 8 **retail** acceptance still needs pad-driven motion vs retail and the
services that sequence reaches (spawn index 1 is cited).

## Related ctests

| Name | Role |
| --- | --- |
| `prototype_task_8` | Disc-free synthetic gate |
| `prototype_task_8_retail` | Skips with code 77 if ALP1.TXT missing |
| `prototype_task_8_smoke_headless` | Disc-free golden checkpoint line, no SDL |
| `prototype_task_8_smoke_headless_retail` | Same line with owner pad; skips 77 if ALP1.TXT or ALP1.PAD is missing |
| `alp1_pad_spawn` | Disc-free fixture decode |
| `alp1_pad_spawn_retail` | Owner `ALP1.PAD` golden spawn |
| `call_80063b34` | Path GPR cite used by handoff |

PROTOTYPE row 9 pipeline: [prototype-task-9.md](prototype-task-9.md).

## Full row 8 (disc-backed)

When the owner extract includes `build/disc/DATA/ALP1.TXT` and companion Alpine
files, the native path below extends synthetic row 8 with file inventory checks
and an optional SDL diagnostic. It loads pad index 1 spawn from `ALP1.PAD` when
present. It does not parse MAP or MDL or compare retail mission physics.

| Piece | Role |
| --- | --- |
| `ctest prototype_task_8_retail` | `tests/test_prototype_task_8_retail.cpp`; skips with code 77 if ALP1.TXT is missing |
| `ctest prototype_task_8` | Unchanged disc-free gate |
| `am3d_mission_slice_smoke --checkpoint` | Writes `build/platform/task8-checkpoint.txt` after the default 8-frame movement script |

Smoke command (from repo root, SDL build):

```text
./build/am3d_mission_slice_smoke --hidden --checkpoint
```

Optional capture: `--capture` writes `build/platform/mission_slice_smoke.bmp`.

`prototype_task_8_retail` checks:

- Opens `ALP1.TXT`; first line contains `Alpine1`
- `ALP1.MAP`, `ALP1.PAD`, and `ALP1.MDL` are regular files with non-zero size under `build/disc/DATA/` (or `disc/DATA/` when cwd is `build/`)
- Loads pad index 1 spawn from `ALP1.PAD` when present; same movement checks as
  synthetic (no retail physics compare)

Checkpoint file columns (space-separated): `Alp1 x z h x2 z2 h2 frames spawn_from_pad mission_path_gpr`.
`x z h` are the spawn. `x2 z2 h2` are the final state. `spawn_from_pad` is 0 or 1.
`mission_path_gpr` is hexadecimal with a `0x` prefix. The formatter is
`format_mission_task8_checkpoint`.

Remaining honesty after this row:

| Limit | Note |
| --- | --- |
| PAD table | Only pad index 1 spawn fields are parsed |
| MAP / MDL use | Inventory only; no geometry load |
| Retail movement compare | Deferred; synthetic z step only |
| Mission gameplay observation | Procedure recorded in [prototype-alp1-movement-observation.md](prototype-alp1-movement-observation.md). No filled run yet. |

## Row 8 complete (retail checkpoint tier)

Named gates, not retail collision, camera, or a pixel compare of the mission.

| Gate | What it locks |
| --- | --- |
| Disc-free | Fixture spawn `50` / `1252` / `50`, 8 frames, final `z` `1316`, handoff GPR `0x800bfdbc`, `spawn_from_pad` 0 |
| Disc-backed | Same movement when owner `ALP1.TXT` and `ALP1.PAD` are present, with `spawn_from_pad` 1 |

Shared runner: `run_prototype_task_8_mission_slice` in
`components/exe/prototype_task_8_mission.cpp`. It calls `record_mission_load_intent`,
resolves start through `mission_movement_start_disc_free` or
`load_alp1_pad_spawn_from_disc_root`, and runs the default 8-frame script.
`prototype_task_8`, `prototype_task_8_retail`, and `prototype_task_8_smoke_headless`
call it. The headless test is disc-free and does not link SDL. Its golden
checkpoint line is:

```text
Alp1 50 1252 50 50 1316 50 8 0 0x800bfdbc
```

Columns: `Alp1 x z h x2 z2 h2 frames spawn_from_pad mission_path_gpr`.
`prototype_task_8_smoke_headless_retail` is the same slice with owner ALP1 files
and skips 77 when `ALP1.TXT` or `ALP1.PAD` is absent. With the owner pad the
line uses `1` in `spawn_from_pad`.

`am3d_mission_slice_smoke --checkpoint` uses the runner and writes that line to
`build/platform/task8-checkpoint.txt`.

External compare (no filled run in this tier):
[prototype-alp1-movement-observation.md](prototype-alp1-movement-observation.md)
(**Operator quick start**: `tools/pcsx/run_alp1_observation.sh` and
`tools/alp1_observation_checklist.py`).

Remaining limits at this tier:

| Limit | Note |
| --- | --- |
| Collision, camera, MAP parse | Not in this slice |
| Pixel retail compare | Not a pass for this tier |
| PAD table | Only pad index 1 spawn fields are parsed |
