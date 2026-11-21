# Prototype playable SDL smoke

Integration note for `am3d_prototype_playable_smoke`. It does not claim retail
in-mission boot or gameplay compare.

## Outcome

`src/prototype_playable_smoke.cpp` runs `run_prototype_playable_pipeline` with
optional owner disc data under `build/disc` or `disc`, then presents diagnostic
frames through SDL.

When `DATA/FRONT.TIM` is present under the resolved disc root, the pipeline
loads those bytes for `run_prototype_task_7_menu_transition` and the smoke
presents two submission frames through `menu_submit_frame`:

1. Menu before Down: owner FRONT quad, `selection_highlight_index` 0 (NEW GAME
   stand-in), green scan marker at `menu_marker_x_a`.
2. After the full pipeline: same FRONT quad, `selection_highlight_index` 1
   (OPTIONS stand-in), green menu marker at `menu_marker_x_b`, plus the blue
   mission progress bar from movement `z` delta.

Without FRONT, the window keeps the disc-free fill diagnostic (dark field, green
menu bar, blue mission bar). One frame. No failure.

## Flags

| Flag | Effect |
| --- | --- |
| `--hidden` | SDL window without pacing hold |
| `--capture` | Writes BMPs under `build/platform/` |
| `--checkpoint` | Writes `build/platform/task9-checkpoint.txt` |

With FRONT and `--capture`:

- `prototype_playable_smoke-menu.bmp` after frame 1
- `prototype_playable_smoke.bmp` after frame 2

Without FRONT, `--capture` writes only `prototype_playable_smoke.bmp`.

## Checks

`ctest prototype_playable_smoke_headless` stays disc-free. It checks the
checkpoint line only. SDL FRONT presentation is manual or local CI with
`AM3D_WITH_SDL2=ON`.

Row 9 composition and headless gates: [prototype-task-9.md](prototype-task-9.md).
CTest and SDL verification: [prototype-verification-runbook.md](prototype-verification-runbook.md).
Menu submission cites: [menu-scan-submission.md](menu-scan-submission.md),
[menu-selection-highlight.md](menu-selection-highlight.md).