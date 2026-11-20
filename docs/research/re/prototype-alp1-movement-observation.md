# ALP1 movement observation

Status: procedure only. No operator run has filled
`build/coordination/alp1-movement-observation/` yet. That directory is
gitignored. This note does not claim a retail physics match, a measured
spawn on screen, or agreement with the host movement script.

Row 8 gaps: [prototype-task-8.md](prototype-task-8.md). Golden pad index 1
spawn `(x, z, heading) = (50, 1252, 50)` is recorded in
[alp1-pad-spawn.md](alp1-pad-spawn.md). The host script that this window is
meant to compare against lives in `tests/test_prototype_task_8.cpp`: four
idle guest frames, then four frames with Cross held.

## Retail setup

Use the same class of run as [first-screen-observation.md](first-screen-observation.md).
Do not copy that note's results into this file until a new ALP1 run records
them.

Planned setup, not a completed run:

- Emulator: PCSX-Redux, interpreter execution, fast boot off.
- Disc: USA, serial SLUS-00491. Record the log disc ID and BIOS label when
  the run exists (the first-screen log reported disc ID `SLUS00491` and BIOS
  `8d8cb7e4`, labeled SCPH-7003 (US)).
- Record the app bundle identifier, binary identity, and dev-build version
  string under `build/coordination/alp1-movement-observation/`. The
  first-screen bundle identified dev build 443, version `7637751d`. Re-read
  `-version` for this run. Do not assume that string still matches.
- Memory cards: task-local files under the portable config directory. Record
  whether both slots are inserted, whether the cards are blank, and whether
  the run loaded a prior save. The first-screen repeat used both slots
  inserted, the first pad connected, and the second pad disconnected. Card
  contents and the numeric controller type were not verified there. Repeat
  that honesty here.
- Pad: one connected pad, same settings as the first-screen note unless this
  run's saved configuration says otherwise. Write the actual settings into
  the run directory. Do not invent them.

Launch from the repository root with a portable directory under `build/`:

```text
-portable build/coordination/alp1-movement-observation/pcsx-config
-interpreter -debugger -run
```

Leave fast boot off (do not pass `-fastboot`). Optional framebuffer helper:
[tools/pcsx/README.md](../../../tools/pcsx/README.md) and
`tools/pcsx/alp1_movement_observation.lua`.

## Controller path to ALP1

High-level steps. Only the menu transition below is already observed. Later
steps stay TBD until an operator records them.

1. Observed boot images, from the first-screen note: Sony Computer
   Entertainment BIOS screen, PlayStation license screen, 3DO logo, Green
   Plastic News intro.
2. Observed: Return for 200 ms during the intro, then `LOADING`, then a
   stable `1 PLAYER` menu with `NEW GAME` white and `OPTIONS` gray.
3. Observed: Down for 100 ms moves the highlight from `NEW GAME` to
   `OPTIONS`. Starting a mission needs `NEW GAME` highlighted. If a run
   lands on `OPTIONS`, move back to `NEW GAME`. The exact key and duration
   for that return are TBD.
4. TBD: confirm `NEW GAME` (host key and duration not yet recorded for a
   mission start).
5. TBD: any difficulty, name, or memory-card prompt between the menu and
   mission select.
6. TBD: mission select control path until the highlight is Alpine 1 / ALP1.
   The owner file header cited by row 8 is `//Alpine1 Mission1` in
   `ALP1.TXT`. The on-screen label is not recorded here.
7. TBD: confirm that mission and wait until the in-mission view is stable
   before the compare window.

Stop the note at the first unknown prompt. Do not guess a button.

## Declared compare window

This is the compare target for a later check against the host script. It is
not proven retail timing.

Host intent, from [prototype-task-8.md](prototype-task-8.md):

| Guest frames | Host `s2` | Intent |
| --- | --- | --- |
| 0 to 3 | `2` | Idle |
| 4 to 7 | `6` | Cross held, synthetic forward |

After the in-mission view looks stable, hold still for about four guest
frames, then hold Cross for about four guest frames, then release. The host
stand-in steps `z` by 16 on each Cross frame and does not apply collision,
camera, or GTE. A retail capture in this window can later be compared with
spawn `(50, 1252, 50)` and with that eight-frame script. Matching frame
counts on the host do not prove the retail game uses the same clock or the
same step size.

## What to record per run

Write these under `build/coordination/alp1-movement-observation/<run-id>/`.
Do not commit that tree.

- Emulator path, `-version` output, and the commit of this repo.
- Disc serial and the log's disc ID and BIOS label.
- Memory-card file names, whether they started blank, and slot insert state.
- Pad settings actually saved for the run.
- Frame number when the in-mission view first looks stable, when the idle
  hold starts, when Cross goes down, and when Cross goes up.
- Optional PNG (or the helper's PPM) paths for those edges. The helper writes
  `frame-NNNNNN.ppm` every N vsyncs. It does not mark button edges.
- Any visible position or heading readout. If the screen has none, write
  "no on-screen position".
- File reads only if a later run adds instrumentation. Until then, write
  "not instrumented".

## Checklist

Empty cells are fine until a run exists.

| Run id | Date | Reach ALP1 (Y/N) | Spawn sanity vs PAD 50 / 1252 / 50 | After-sequence position notes | Capture paths |
| --- | --- | --- | --- | --- | --- |
| | | | | | |

## Limits

- No game code changes in this procedure.
- Captures, logs, memory cards, and portable emulator config stay under
  `build/`. They do not go in git.
- Reaching ALP1, or saving frames, does not show that retail movement matches
  the host `z` step.
- Collision, camera, and mission gameplay remain open in the row 8 gaps.
