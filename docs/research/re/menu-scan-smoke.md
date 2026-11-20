# Menu scan SDL smoke integration

This is an integration note. It does not claim PROTOTYPE task 7 pass, a
retail menu transition, or live controller wiring into `PadGetState`.

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

## Synthetic inputs

The released-slot table pattern matches
`tests/test_menu_input_scan_loop.cpp`. `pad_get_state` always returns `2`.
No retail table dump, stack words at `sp+0x1c` or `sp+0x28`, or SDL pad
mapping is wired here.

## Checks

`tests/test_menu_scan_smoke_headless.cpp` runs two scan frames without SDL.
The visible target is manual or local CI with `AM3D_WITH_SDL2=ON`. A
dummy-driver pass alone does not prove a visible window works.

## Gap

Retail menu update, textured geometry from reconstructed submission, live
pad bytes, and observed screen transition remain open for task 7.