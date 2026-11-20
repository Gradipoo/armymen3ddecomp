# SDL PadGetState mapping for menu scan smoke

Integration note. Does not claim PROTOTYPE task 7 pass or a retail menu
transition.

## Retail cite

[call-80064e58.md](call-80064e58.md) records the return at `0x80064e58`. The
caller stores `v0` in `s2` and tests unsigned less than seven. Sampled
captures had `s2=2` and fell through to `0x80064e68`. The indirect table at
`0x800c3e98` used index two and loaded destination `0x80064f14`.

[call-80064e40.md](call-80064e40.md) builds `PadGetState` argument
`(stack_word_18 << 4) | s7` in `s3`. Retail `PadGetState` entries used `a0=0`.
Our helper ignores the port word until `sp+0x18` is cited.

## Host mapping

`components/platform/menu_pad_get_state.cpp` maps SDL
`PadState::buttons` (cleared bit means held) to the unsigned word passed
through `pad_get_state` into `call_80064e40`:

| Host control | Bit in `PadState` | Return (s2) |
| --- | --- | --- |
| idle | all released | 2 |
| D-pad Up | 4 | 1 |
| D-pad Down | 6 | 3 |
| D-pad Left | 7 | 4 |
| D-pad Right | 5 | 5 |
| Cross / A | 13 | 6 |

Down wins when Up and Down are both held. Returns stay below seven so
`below_seven` stays set per `call_80064e40.cpp`.

These direction indices are provisional. Retail kept `s2=2` while the
principal moved from NEW GAME to OPTIONS. The exact `PadGetState` body at
`0x80094fe0` is not entered in our notes. Selection may also use table bytes
and not only `s2`.

## Scan glue limit

`menu_input_scan_step` cites dispatch `0x80064f14` when `s2==2`
([call-80064e58.md](call-80064e58.md)). Optional `test_inject_pad_dispatch`
supplies per-index table words in ctests and through
`run_menu_input_scan_frames`. Index three (Down) may inject a provisional
`0x80064f14` for glue tests only; live RAM at `0x800c3ea4` is unstated.
Indices 0, 1, 4, 5, and 6 still have no cited destination. Gap 3 (scripted
table sequence) remains open.

## Smoke wiring

`src/menu_scan_smoke.cpp` polls each frame (once before `--batch`), stores
buttons in module state, and passes `pad_get_state_from_poll` into
`run_menu_input_scan_frames`. With `--inject-down`, the same path passes
`menu_scan_down_dispatch_inject()` so index three can reach the provisional
tail cite. Headless ctests keep a fixed `2` stub unless
`kMenuScanHeadlessInjectDown` is enabled.

## Checks

`ctest -R menu_scan_pad_get_state` exercises the mapping without SDL.
`am3d_menu_scan_smoke` needs `AM3D_WITH_SDL2=ON` and a controller or
keyboard-mapped gamepad.