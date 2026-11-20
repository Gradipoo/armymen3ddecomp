# PROTOTYPE task 9 synthetic acceptance (menu-to-mission pipeline)

Status: **synthetic** met at `23b6014`; **disc-backed row 9** when owner
`ALP1.TXT` is present (`ctest prototype_task_9_retail`). No retail
in-mission boot or gameplay compare.

[PROTOTYPE.md](../../PROTOTYPE.md) row 9: one host **playable pipeline**
composes rows 7 and 8 without widening physics or GPU scope.

## Composition

| Stage | Source row | Host entry |
| --- | --- | --- |
| Menu multi-frame scan | Row 7 phase A | `run_menu_input_scan_frames` + `MenuTableSequencer` |
| Optional Down dispatch | Row 7 phase B | `menu_input_scan_host_resume` + `PadStateDispatchInject` |
| Mission load intent | Row 8 handoff | `record_mission_load_intent()` |
| ALP1 movement script | Row 8 slice | `prototype_playable_default_mission_script` + `run_mission_movement_frames` |

Frame budgets (defaults): menu `4`, down `1`, mission `8`. Disc-free spawn
stays `100`/`200`/`0`; `prototype_task_9_retail` fills movement start from
`ALP1.PAD` pad index 1 when the owner extract is present.

## API

| Piece | Path |
| --- | --- |
| Config / result / runner | `components/exe/prototype_playable_pipeline.hpp` |
| Implementation | `components/exe/prototype_playable_pipeline.cpp` |

`run_prototype_playable_pipeline` takes `pad_get_state` for menu/down scan
only. Mission frames use the fixed eight-frame script (idle then Cross).

## Checks

`ctest prototype_task_9` (disc-free):

- `frames.menu == 4`, `frames.down == 1`, `frames.mission == 8`
- `menu_s7_after_menu_budget == 8` after four scan frames
- Down dispatch: `destination_stated`, `destination == 0x80064f14`, word `0x800c3ea4`, `tail_ran`
- `mission_path_gpr == 0x800bfdbc`
- Movement `z` increased; `x` and `heading` unchanged

`ctest prototype_task_9_retail` when `build/disc/DATA/ALP1.TXT` exists:

- Same pipeline; TXT header cites Alpine1
- Skips with code 77 when ALP1.TXT is missing

SDL smoke (`am3d_prototype_playable_smoke --hidden --checkpoint`):

- Writes `build/platform/task9-checkpoint.txt` through `format_prototype_playable_checkpoint_line`
- Column order: `menu_s7_after_menu_budget`, `menu_s7`, mission `z`, `frames.menu`, `frames.down`, `frames.mission`, `mission_path_gpr` (`0x` hex), movement start `x`, `z`, `heading`, `spawn_from_pad` (`1` when pad index 1 loaded, else `0`)
- Optional `--capture` → `build/platform/prototype_playable_smoke.bmp`

`ctest prototype_playable_smoke_headless` (disc-free, no window):

- Synthetic start `100`/`200`/`0`, idle pad
- Formatted line `8 9 264 4 1 8 0x800bfdbc 100 200 0 0`
- `spawn_from_pad` is `0`

Related row notes: [prototype-task-7.md](prototype-task-7.md),
[prototype-task-8.md](prototype-task-8.md).

## Gaps (honest limits)

| Gap | Note |
| --- | --- |
| Retail mission boot | No reconstructed mission main or ALP1 asset load in the pipeline |
| Menu GPU / FRONT.TIM | Pipeline is headless; smoke uses fill diagnostic only |
| `PadGetState` body | Host stub; not retail pad driver |
| Live `0x800c3ea4` | Provisional Down inject only |
| Gameplay | Fixed script; no observation-backed mission loop |

Coordination state: `build/coordination/prototype-playable/state.md`.