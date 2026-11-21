# Menu scan submission integration

This note links the menu scan SDL smoke to the reconstructed submission
wrapper. It does not claim PROTOTYPE task 7 pass, a retail menu transition,
or retail ordering-table replay.

## Outcome

`components/platform/menu_submit_frame.{hpp,cpp}` implements a bounded 16
KiB synthetic RAM window at guest base `0x800c8000`. A local list adapter
flattening pass accepts fill `0x02`, image upload `0xa0`, and semi-transparent
textured quad `0x2f`, routing supported packets into `FillVram`. The bridge
implements `SubmitOrderingTableGpu` and calls `call_8007c11c` with the
observed menu capture arguments `0x800c8518` and `0x900`. The zero branch is
fixed because the menu samples loaded zero at `gp+0x0c` after `DrawSync`.
See [call-8007c11c.md](call-8007c11c.md).

The ordering table holds `0x900` empty slot tags and a separate command node
with a background fill and diagnostic `0x2f` quad. That shape follows the
[synthetic submission integration](native-submit-integration.md). Links use byte
offsets into the synthetic region, not host pointers derived from guest
values.

Optional `DATA/FRONT.TIM` bytes pass through public `upload_front_tim` into
VRAM before list submission. The marker still uses `fill_display` after the
wrapper returns. Quad placement `(234,56)` plus display origin is a stand-in.

`src/menu_scan_smoke.cpp` accepts `--submit` to use this path. The default
fill-only presentation path remains for disc-free CI.

## Checks

`tests/test_menu_submit_frame.cpp` runs without SDL. It expects one
`DrawSync`, `DrawOTag` address `0x800ca914`, an accepted list, return `1`, and
a green marker pixel.

## Limits

This is not the PS1Recomp GPU candidate used in the local coordination trial.
Semi-transparent blending and retail mask state are not reproduced. The
`0x900` slots reserve observed table size; only the tail chain and command
node carry drawable data. Live pad bytes, `PadGetState` at `0x80064e58`,
reconstructed menu update, and an observed screen transition remain open for
task 7.