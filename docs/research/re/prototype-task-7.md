# PROTOTYPE task 7 synthetic acceptance

Status: **synthetic** met at `0d979fc`; **disc-backed row 7** met at `dfcf309` when
owner `FRONT.TIM` is present (`ctest prototype_task_7_retail`).
Automated pixel match vs retail is not claimed; see limits below.

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

## Full row 7 (disc-backed)

When the owner extract includes `build/disc/DATA/FRONT.TIM`, the native path
below extends synthetic `0d979fc` with FRONT.TIM load, `menu_submit_frame`,
and the same Down transition cite as phase B.

| Piece | Role |
| --- | --- |
| `ctest prototype_task_7_retail` | `tests/test_prototype_task_7_retail.cpp`; skips with code 77 if FRONT.TIM is missing |
| `ctest prototype_task_7` | Unchanged disc-free gate |
| `am3d_menu_scan_smoke --checkpoint` | Writes `build/platform/task7-checkpoint.txt` after batch scripted submit |
| `python3 tools/prototype_task7_compare.py` | Owner-local 64x64 center mean abs diff vs retail PNG; not a CI gate |
| [prototype-task-7-pixel-checkpoint.md](prototype-task-7-pixel-checkpoint.md) | Local capture and compare procedure |

Smoke command (from repo root, SDL build):

```text
./build/am3d_menu_scan_smoke --batch --scripted --submit --hidden --frames 4 --checkpoint
```

Retail checkpoint names (no pixels in repo): [first-screen-observation.md](first-screen-observation.md)
run5 `menu-before.png` from frame 3720 (`NEW GAME` white) and `menu-after.png`
from frame 5040 (`OPTIONS` white after Down). Compare tool defaults to those
paths when present under `build/coordination/retail-screen/`.

`prototype_task_7_retail` checks:

- Phase A: four `run_menu_input_scan_frames` steps with `MenuTableSequencer`,
  tail bytes `0x0b`/`0x87`, `menu_submit_frame` with owner FRONT bytes, green
  marker at `200 + s7*12`, and a non-zero sample in the stand-in rect at
  origin `(0,0)` offset `(234,56)`.
- Phase B: `menu_input_scan_host_resume` then one Down step (`s2=3`, inject).
  Expect dispatch `0x800c3ea4`, `tail_ran`, `s7` bumps by one, and a second
  `menu_submit_frame` with an advanced marker.

Remaining honesty after this row:

| Limit | Note |
| --- | --- |
| Pixel-exact retail match | Manual when owner BMP/PNG exist; compare tool reports diff only |
| `PadGetState` body | Host stub in ctest; SDL mapping in smoke |
| Live `0x800c3ea4` | Provisional inject; no RAM dump of the dispatch table |
| Full retail scene loop | Submission slice plus scan glue, not reconstructed retail menu main |

Mission movement disc-backed row: [prototype-task-8.md](prototype-task-8.md) Full row 8.