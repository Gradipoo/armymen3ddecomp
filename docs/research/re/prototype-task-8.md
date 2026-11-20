# PROTOTYPE task 8 synthetic acceptance

Status: **synthetic** met at this change; **disc-backed row 8** when owner
`ALP1.TXT` is present (`ctest prototype_task_8_retail`). Retail movement,
collision, camera, and gameplay comparison are deferred.

## Mission choice

**ALP1** (Alpine mission 1). Owner files live under `build/disc/DATA/`:
`ALP1.TXT` (header `//Alpine1 Mission1`), plus companion `.MAP`, `.PAD`,
`.MDL`, and related assets. This slice declares paths only. It does not
parse MAP, MDL, PAD, or TXT.

Load-path research (not executed here): [mission-ini-loop.md](mission-ini-loop.md)
and [call-80063b34.md](call-80063b34.md) cite `call_80063b34` on the
`\mission.ini` loop returning path GPR `0x800bfdbc`.

## Start state

Host stand-in in `MissionMovementStartState`:

| Field | Synthetic test value | Retail gap |
| --- | --- | --- |
| `x` | `100` | Not from ALP1.PAD spawn |
| `z` | `200` | Forward axis stand-in only |
| `heading` | `0` | No cited spawn yaw |

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
| Frame runner | `components/exe/mission_movement_slice.cpp` |
| Menu load cite | `components/exe/mission_menu_handoff.hpp` |

## Remaining gaps (honest limits)

| Gap | Note |
| --- | --- |
| ALP1.PAD spawn | Start state is arbitrary host ints |
| MAP / MDL collision | No geometry load or blocking |
| Camera | No mission camera chain |
| GTE / animation | No retail body update |
| Retail movement compare | Deferred; synthetic z step only |
| Mission gameplay | No in-mission observation record yet |

Row 8 **retail** acceptance still needs cited spawn, pad-driven motion vs
retail, and the services that sequence reaches.

## Related ctests

| Name | Role |
| --- | --- |
| `prototype_task_8` | Disc-free synthetic gate |
| `prototype_task_8_retail` | Skips with code 77 if ALP1.TXT missing |
| `call_80063b34` | Path GPR cite used by handoff |

PROTOTYPE row 9 pipeline: [prototype-task-9.md](prototype-task-9.md).

## Full row 8 (disc-backed)

When the owner extract includes `build/disc/DATA/ALP1.TXT` and companion Alpine
files, the native path below extends synthetic row 8 with file inventory checks
and an optional SDL diagnostic. It does not parse MAP, PAD, or MDL or compare
retail mission physics.

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
- Same synthetic movement checks as `prototype_task_8` (no retail position compare)

Checkpoint file columns (space-separated): mission id `Alp1`, final `x`, `z`,
`heading`, `frames_run`.

Remaining honesty after this row:

| Limit | Note |
| --- | --- |
| ALP1.PAD spawn | Start state is still arbitrary host ints |
| MAP / MDL use | Inventory only; no geometry load |
| Retail movement compare | Deferred; synthetic z step only |
| Mission gameplay observation | No in-mission retail screen record yet |
