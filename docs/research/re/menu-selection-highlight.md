# Menu selection highlight stand-in

The first-screen observation records `NEW GAME` white, then `OPTIONS` white
after Down. See [first-screen-observation.md](first-screen-observation.md).
This note does not claim those glyphs, their GPU packets, or a retail
selection byte.

`draw_menu_selection_highlight` paints two thin bars on the FRONT quad used by
`menu_submit_frame` (`quad_x` 234, `quad_y` 56 unless the request overrides
them):

| Row | Story label | Offset from quad origin | Size | Color when selected |
| --- | --- | --- | --- | --- |
| 0 | `NEW GAME` | y + 80 | 120 by 2 | `0xffffff` |
| 1 | `OPTIONS` | y + 100 | 120 by 2 | `0xffffff` |

The other row is filled with `0x404040`. The VRAM sink stores 5-bit channels, so that gray reads back as `0x424242`. `MenuSubmitFrameRequest::selection_highlight_index`
selects the row. `0` emphasizes the first row. `1` emphasizes the second.
Any other value skips the bars.

`run_prototype_task_7_menu_transition` maps phase A to index 0 and the Down
step to index 1. That mapping is an observation-aligned stand-in. It is not a
load from retail RAM.

Gap versus retail: the game draws menu text through GPU primitives. These bars
do not parse that text, do not match glyph pixels, and do not move with a
live selection word.