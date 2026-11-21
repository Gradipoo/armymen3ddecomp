# PROTOTYPE task 5 retail checkpoint tier

Status: **synthetic** met through `front_tim` and `prototype_task_5`;
**disc-backed** when owner `DATA/FRONT.TIM` is present
(`ctest prototype_task_5_retail`). A decoded picture or upload replay is not a
running menu scene.

## Measured layout

Owner file layout, VRAM rectangle cites, and paint placement are recorded in
[front-tim.md](front-tim.md). The public reader accepts that field order for any
size whose block lengths match the rectangles. Native `upload_front_tim` sends
the color table then packed pixel words through a caller sink without decoding
texels. `paint_front_tim` decodes 4-bit indices into `FillVram` at a host origin.

Retail upload rectangles from the measured file: palette `(512, 506, 16, 1)`,
pixels `(640, 0, 11, 128)`. The smoke window paints at x `234`, y `56` relative
to the drawing page origin per [front-tim.md](front-tim.md).

## Disc-free fallback

When `DATA/FRONT.TIM` is absent, `am3d_platform_smoke` keeps the synthetic color
bars and does not call `paint_front_tim`. The default build and CI stay disc-free.

Prototype smoke and retail tests load owner bytes through
`platform::load_front_tim_disc_bytes` (`disc_front_tim_load.hpp`), capped at
2880 bytes via `read_disc_data_file`.

## Checks

| Name | Role |
| --- | --- |
| `ctest prototype_task_5` | Wraps `front_tim` (`test_front_tim`): synthetic bytes exercise `paint_front_tim` and `upload_front_tim`, bounds, and rejection paths |
| `ctest prototype_task_5_retail` | Skips with code 77 if `build/disc/DATA/FRONT.TIM` is missing; validates 2880-byte owner layout against [front-tim.md](front-tim.md), upload order and rectangles, and 44 by 128 paint at `(234, 56)` |
| `ctest front_tim` | Underlying disc-free gate shared with row 5 |

`prototype_task_5_retail` checks:

- File size `2880`, file mark `0x10`, flag `0x8`, block lengths `0x2c` and `0x0b0c`
- Color-table halfwords `512`, `506`, `16`, `1`; first stored color `0x5335`
- Pixel-block halfwords `640`, `0`, `11`, `128`
- Two upload calls with word counts `16` and `1408`
- Painted picture size 44 by 128 with at least one non-zero pixel in the placement band

## Honest limits

| Gap | Note |
| --- | --- |
| Running menu loop | No reconstructed update or retail frame compare at this row |
| GPU texture path | Upload sink is tested; `fill_vram` still rejects non-fill GPU packets |
| Screen placement | Smoke coordinates remain a stand-in; not a retail framebuffer match |
| Row 7 menu scan | Menu transition and selection highlight are row 7 scope |

Rows 7 through 9 retail checkpoint tier: [prototype-task-7.md](prototype-task-7.md),
[prototype-task-8.md](prototype-task-8.md), [prototype-task-9.md](prototype-task-9.md).