# Menu table byte sequence integration

This is an integration note. It does not claim PROTOTYPE task 7 pass or retail
menu capture.

`MenuTableSequencer` in `components/exe/menu_table_sequence.cpp` patches one
4-byte scan table slot before each step in
[menu-input-scan-loop](menu-input-scan-loop.md) when
`run_menu_input_scan_frames` receives a non-null `table_sequencer` pointer.
`apply_frame` writes at the current `scan.table_cursor` so the slot index
advances with the cited `table_cursor += 4` tail stores.

## Slot bytes

Patterns match `tests/test_menu_input_scan.cpp` and
[menu-input-scan](menu-input-scan.md):

| Pattern | Bytes | Tail at `record+0xb` (Up path uses `s7` 1) |
| --- | --- | --- |
| released | `00 41 ff ff` | `0x00` on the clear tail |
| up | `00 41 ef ff` | `0x80` via [call-800650d0](call-800650d0.md) |

The second byte stays `0x41` so [call-80064f14](call-80064f14.md) keeps the
measured compare path. Halfword `0xefff` supplies complemented bit `0x10`
for the Up tail.

## Script

`step_index` advances on every loop hook invocation so separate
`run_menu_input_scan_frames` calls with `count` 1 still alternate patterns.
Even indices patch released. Odd indices patch up. Across two frames with
`PadGetState` fixed at `2`, frame 0 and frame 1 produce distinct
tail bytes (`record+0xb` then `record+0x7c+0xb` after the cited stride) and
increment `scan.s7`. That is a disc-free stand-in for moving between OPTIONS
and NEW GAME table slots, not a retail table dump.

## Checks

`ctest -R menu_table_sequence` runs `tests/test_menu_table_sequence.cpp`.
`menu_scan_smoke_headless` uses the same sequencer hook. SDL smoke may pass
the sequencer when `--scripted` is set or for multi-frame runs; see
[menu-scan-smoke](menu-scan-smoke.md).

## Gap

Retail table layout, live bytes at `sp+0x18`, compare word `== 4`, and
observed controller transitions stay open for task 7.