# PROTOTYPE task 7 pixel checkpoint (local)

This records owner-local comparison between native smoke output and retail
menu captures. It does not pass or fail CI. Retail images stay under
`build/coordination/retail-screen/`.

## Native capture command

From repo root after `cmake -S . -B build -DAM3D_WITH_SDL2=ON`:

```text
./build/am3d_menu_scan_smoke --batch --scripted --submit --inject-down --hidden \
  --frames 4 --checkpoint --capture
```

Outputs:

- `build/platform/menu_scan_smoke.bmp` (diagnostic FRONT.TIM + submission marker)
- `build/platform/task7-checkpoint.txt` fields: `s7`, tail `0x0b`, tail `0x87`,
  `--frames`, `has_front_tim`, `submit`, `batch_scan_frames_run`

## Retail anchors

[first-screen-observation.md](first-screen-observation.md): run5 frame 3720
(`NEW GAME` white) and frame 5040 (`OPTIONS` white after Down). Local copies may
appear as `build/coordination/retail-screen/run5/` or `run11/` PNG/BMP.

## Compare tool

```text
python3 tools/prototype_task7_compare.py build/platform/menu_scan_smoke.bmp \
  build/coordination/retail-screen/run11/menu-before.png
python3 tools/prototype_task7_compare.py build/platform/menu_scan_smoke.bmp \
  build/coordination/retail-screen/run11/menu-after.png
```

Reports center 64x64 mean absolute channel difference. High values are expected:
native output is a diagnostic submission slice (stand-in quad placement), not a
reconstructed retail menu framebuffer.

One local sample (Nov 20, 2026): native `menu_scan_smoke.bmp` vs run11
`menu-before.png` MAD **83.7**; vs `menu-after.png` MAD **84.9**. Not a pass gate.

## Gap

Pixel-exact agreement is not claimed. The compare tool is a manual regression
aid only. Selection highlight and full 1 PLAYER layout are not reproduced.