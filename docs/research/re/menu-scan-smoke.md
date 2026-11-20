# Menu scan SDL smoke integration

This is an integration note. It does not claim PROTOTYPE task 7 pass or a
retail menu transition.

## Outcome

`src/menu_scan_smoke.cpp` is an optional SDL target
`am3d_menu_scan_smoke`, gated like `am3d_platform_smoke` by
`AM3D_WITH_SDL2`. Each presented frame runs one host scan iteration
through `run_menu_input_scan_frames` with `count` 1. The default frame
budget is 4, matching the synthetic `menu_scan_should_loop` limit in
[menu-input-scan-loop.md](menu-input-scan-loop.md).

After each scan step, drawing reuses the platform smoke pattern: synthetic
color bars when `build/disc/DATA/FRONT.TIM` is absent, otherwise the
measured 4-bit picture at the same stand-in offset as
[front-tim.md](front-tim.md). A 16-pixel marker tracks `scan.s7` on the
horizontal axis only. That placement is diagnostic, not measured menu
layout.

`--batch` runs `run_menu_input_scan_frames` once for the full `--frames`
budget, then presents a single diagnostic frame. It does not pace multiple
SDL updates across scan steps.

## Pad input

The released-slot table pattern matches
`tests/test_menu_input_scan_loop.cpp`. Live SDL poll feeds
`menu_scan_pad_get_state` through `pad_get_state_from_poll`. Mapping and
retail cites are in [menu-scan-pad-sdl.md](menu-scan-pad-sdl.md). Headless
ctest keeps a fixed `2` stub.

When `--scripted` is set or `--frames` is greater than 1,
`run_menu_input_scan_frames` uses [menu-table-sequence](menu-table-sequence.md)
to patch released and up slots per frame at `scan.table_cursor`.

Host `MenuInputScanIndices` keeps `stack_word_18` at zero to match retail
`PadGetState` `a0=0` in [call-80064e58.md](call-80064e58.md). The synthetic
loop limit is passed as `stack_word_1c` (default four in `ScanHostState`).
Optional `stack_word_28` is wired through `run_menu_input_scan_frames` for the
compare-four tail; see [menu-scan-stack-hooks.md](menu-scan-stack-hooks.md).
Retail table dumps and live stack limits stay unstated.

## Checks

`tests/test_menu_scan_smoke_headless.cpp` runs two scan frames without SDL.
The visible target is manual or local CI with `AM3D_WITH_SDL2=ON`. A
dummy-driver pass alone does not prove a visible window works.

## Gap

Retail menu update, textured geometry from reconstructed submission,
dispatch words for `s2` other than two, and observed screen transition
remain open for task 7.