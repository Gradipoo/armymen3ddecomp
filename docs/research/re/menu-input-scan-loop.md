# Menu input scan loop integration

This is an integration note. It is not a boot note and it does not resume
the parked lane at `0x80061fe4`. It does not claim PROTOTYPE task 7 or
retail multi-frame menu behavior.

`run_menu_input_scan_frames` in `components/exe/menu_input_scan_loop.cpp`
calls [menu-input-scan](menu-input-scan.md) `menu_input_scan_step` in a
host loop. The stop rule matches the synthetic compare in
[call-8006518c](call-8006518c.md): each tail sets `loop_again` from
`menu_scan_should_loop` on `scan.s7` and the caller `stack_word_1c`. The outer
loop also stops when the frame `count` budget reaches zero.

Before each step, `menu_table_index` is set from `scan.table_cursor` and
`fp` is taken from `scan.fp`. That follows the tail updates in
[call-800650f4](call-800650f4.md) and [call-800650d0](call-800650d0.md)
without entering the taken re-entry body at `0x80064e40` from
[call-8006518c](call-8006518c.md). The portable step still uses
`scan.s7` as the loop-head `s7` argument for [call-80064e40](call-80064e40.md).

## Synthetic check

`tests/test_menu_input_scan_loop.cpp` repeats the released table pattern,
keeps `PadGetState` at `2`, and runs until `s7` meets a synthetic limit.
That checks increment and stop only. It is not a retail capture.

Optional per-frame table patching uses `MenuTableSequencer`; see
[menu-table-sequence.md](menu-table-sequence.md). Headless smoke passes it for
two frames.

Optional `stack_word_28` hooks the compare-four tail at `0x80065168`; see
[menu-scan-stack-hooks.md](menu-scan-stack-hooks.md). Default `stack_word_18`
is zero per [call-80064e58.md](call-80064e58.md).

## Gap

Optional SDL wiring lives in
[menu-scan-smoke.md](menu-scan-smoke.md). Live retail limits at `sp+0x1c` and
`sp+0x28`, and table layout beyond the repeated host pattern, stay unstated.
When the last step stops looping, [call-80065194](call-80065194.md)
records the `bne` on post-tail `s5` (`scan.index`). The body at
`0x800651c8` stays unentered.