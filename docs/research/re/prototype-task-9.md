# PROTOTYPE task 9 synthetic acceptance (menu-to-mission pipeline)

Status: **synthetic** met at `23b6014`; **disc-backed row 9** when owner
`ALP1.TXT` is present (`ctest prototype_task_9_retail`). No retail
in-mission boot or gameplay compare.

[PROTOTYPE.md](../../PROTOTYPE.md) row 9: one host **playable pipeline**
composes rows 7 and 8 without widening physics or GPU scope.

## Composition

| Stage | Source row | Host entry |
| --- | --- | --- |
| Menu scan and Down | Row 7 | `run_prototype_task_7_menu_transition` |
| Mission load and movement | Row 8 | `run_prototype_task_8_mission_slice` |

`run_prototype_playable_pipeline` calls those two runners. It does not scan
the menu table or step movement itself. Frame budgets stay the runner
defaults: menu `4`, down `1`, mission `8`. Disc-free spawn is the ALP1.PAD
index 1 fixture (`50`/`1252`/`50`). A non-empty `config.disc_root` is passed
to the row 8 runner so pad index 1 loads when the owner extract is present.

## API

| Piece | Path |
| --- | --- |
| Config / result / runner | `components/exe/prototype_playable_pipeline.hpp` |
| Implementation | `components/exe/prototype_playable_pipeline.cpp` |

`run_prototype_playable_pipeline` requires a non-null `pad_get_state`. The
row 7 runner reads the pad through `prototype_task_7_pad_get_state` (2 until
`s7` reaches 8, then 3). Mission frames stay the row 8 eight-frame script
(idle then Cross). `config.disc_root` empty keeps the fixture.

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
- Disc-free: one fill diagnostic frame (green menu bar, blue mission bar)
- With owner `disc_root/DATA/FRONT.TIM`: two `menu_submit_frame` frames (highlight 0 then 1) plus mission bar on the second frame. See [prototype-playable-smoke.md](prototype-playable-smoke.md)
- Optional `--capture`: `prototype_playable_smoke-menu.bmp` and `prototype_playable_smoke.bmp` when FRONT is present; otherwise `prototype_playable_smoke.bmp` only

`ctest prototype_playable_smoke_headless` (disc-free, no window):

- Synthetic start `50`/`1252`/`50` from the pad fixture, idle pad
- Formatted line `8 9 1316 4 1 8 0x800bfdbc 50 1252 50 0`
- `spawn_from_pad` is `0`

Related row notes: [prototype-task-7.md](prototype-task-7.md),
[prototype-task-8.md](prototype-task-8.md).

## Row 9 complete (retail checkpoint tier)

Named gates, not a retail in-mission boot and not a gameplay compare. The
pipeline chains the row 7 and row 8 runners. Frame budgets stay 4, 1, and 8.
The checkpoint line is unchanged.

| Gate | What it locks |
| --- | --- |
| Row 7 menu | `run_prototype_task_7_menu_transition`: `s7` 8 after four frames, `s7` 9 after one Down step, dispatch word `0x800c3ea4`, destination `0x80064f14`, `tail_ran` |
| Row 8 mission | `run_prototype_task_8_mission_slice`: handoff GPR `0x800bfdbc`, 8 frames, final `z` `1316` from fixture start `50` / `1252` / `50` when `disc_root` is empty |
| Disc-backed mission | Same row 8 runner with `config.disc_root` set. `spawn_from_pad` is 1 when `ALP1.PAD` pad index 1 loads |
| Headless checkpoint | `prototype_playable_smoke_headless` line `8 9 1316 4 1 8 0x800bfdbc 50 1252 50 0` |

`prototype_task_9`, `prototype_task_9_retail`, and
`prototype_playable_smoke_headless` call `run_prototype_playable_pipeline`.
Retail skips with code 77 when `ALP1.TXT` is missing. Headless tier stays
fill-free; SDL smoke optionally paints FRONT when the owner file is present.

## Gaps (honest limits)

| Gap | Note |
| --- | --- |
| Retail mission boot | No reconstructed mission main or ALP1 asset load in the pipeline |
| Menu GPU / FRONT.TIM | Headless tests omit SDL; smoke uses `menu_submit_frame` when FRONT is present |
| `PadGetState` body | Host stub; not retail pad driver |
| Live `0x800c3ea4` | Provisional Down inject only |
| Gameplay | Fixed script; mission loop observation still open. ALP1 movement capture is procedure only: [prototype-alp1-movement-observation.md](prototype-alp1-movement-observation.md). |

Coordination state: `build/coordination/prototype-playable/state.md`.
