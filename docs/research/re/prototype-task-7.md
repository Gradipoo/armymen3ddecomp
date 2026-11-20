# PROTOTYPE task 7 synthetic acceptance

Status: **synthetic / disc-free acceptance met** at integration commit `0d979fc`.
This does not pass the full row in [PROTOTYPE.md](../../PROTOTYPE.md): no
reconstructed retail GPU scene, no live dispatch table at `0x800c3ea4`, and no
pixel agreement with retail at every checkpoint.

Retail comparison anchor: [first-screen-observation.md](first-screen-observation.md)
(PCSX-Redux `SLUS-00491`, Down 100 ms between `NEW GAME` and `OPTIONS`
highlight). That record is the named checkpoint for a later native run with
owner files. This note only wires our synthetic path to the same transition
story at table-tail and dispatch cites.

## Executable and smoke identity

- **Integration commit:** `0d979fc` (menu scan acceptance; chain through `842aa0f` / `9200c50`).
- **Multi-frame path:** `run_menu_input_scan_frames` in
  `components/exe/menu_input_scan_loop.cpp`, same glue as
  `am3d_menu_scan_smoke` / `test_menu_scan_smoke_headless`.
- **Synthetic ctest:** `prototype_task_7` (`tests/test_prototype_task_7.cpp`).
- **Related ctests (unchanged):** `menu_scan_smoke_headless`,
  `menu_input_scan_loop`, `menu_input_scan`.

## Phase A: multi-frame menu update (disc-free)

Four host scan steps with `MenuTableSequencer` alternate released and up slot
bytes per [menu-table-sequence.md](menu-table-sequence.md). `PadGetState` stays
at synthetic `2` (retail cite: [call-80064e58.md](call-80064e58.md), `a0=0`).

Checks in `prototype_task_7`:

- `frames_run == 4`
- `scan.s7 == 8` after the budget (diagnostic counter, not retail layout)
- Record tail bytes at `record+0x0b` and `record+0x7c+0x0b` (`0x87` after frame-1
  stride): `0x00` and `0x80`, matching `menu_scan_smoke_headless` sequencer half
- `tail_ran` on the last step

That is a stand-in for **multiple frames** and **OPTIONS ↔ NEW GAME** table
motion (released vs up tails), not a measured retail table dump.

## Phase B: controller transition stand-in (Down / `s2=3`)

One frame with `pad_get_state` returning `3` and `PadStateDispatchInject` with
`entry[3] = 0x80064f14` (provisional; live RAM unstated per
[call-80064e68.md](call-80064e68.md)):

- Dispatch word address `0x800c3ea4` (index three; index two remains `0x800c3ea0`
  in `menu_input_scan_loop`)
- `destination_stated`, destination `0x80064f14`, `tail_ran`

Mirrors the Down half of `test_menu_input_scan_loop` and optional
`--inject-down` in [menu-scan-smoke.md](menu-scan-smoke.md). SDL smoke still
defaults to no inject in CI.

## Remaining gaps (honest limits)

| Gap | Note |
| --- | --- |
| Live word at `0x800c3ea4` | Provisional inject only; no retail RAM dump of the pad dispatch table |
| `PadGetState` body | Host stub / SDL poll mapping; not reconstructed retail pad driver |
| GPU submission / scene | `menu_submit_frame` and fill sink are partial; no textured retail menu loop |
| Retail table bytes | Sequencer patterns are cited tail stand-ins, not a capture of `sp+0x18` slots |
| Visible transition | Observation linked above; synthetic ctest does not compare framebuffer pixels |

Row 7 **retail** acceptance still needs owner files, reconstructed update plus
submission, and checkpoint comparison beyond this integration note.