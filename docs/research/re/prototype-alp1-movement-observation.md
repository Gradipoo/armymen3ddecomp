# ALP1 movement observation

Status: **partial operator report** (2026-11-21). Menu-to-mission path is
recorded once without frame numbers or PCSX capture paths. Mission identity
(ALP1 vs another map) is **not verified** on that report. A local run may
exist under `build/coordination/alp1-movement-observation/`; see
[prototype-alp1-run-handoff.md](prototype-alp1-run-handoff.md). That
directory is gitignored. This note does not claim a retail physics match, a
measured spawn on screen, or agreement with the host movement script.

Row 8 gaps: [prototype-task-8.md](prototype-task-8.md). Golden pad index 1
spawn `(x, z, heading) = (50, 1252, 50)` is recorded in
[alp1-pad-spawn.md](alp1-pad-spawn.md). The host script that this window is
meant to compare against lives in `tests/test_prototype_task_8.cpp`: four
idle guest frames, then four frames with Cross held.

## Operator quick start

Run from the repository root on the machine that owns the USA cue. Set
`AM3D_DISC` to the cue path, or pass it as the first argument to the script.

```sh
export AM3D_DISC="/path/to/Army Men 3D (USA).cue"
sh tools/pcsx/run_alp1_observation.sh
```

The script creates
`build/coordination/alp1-movement-observation/<run-id>/` with UTC
`run-id` (`YYYYMMDD-HHMMSS`), writes `session.txt` (including PCSX-Redux
`-version` when the binary is present), calls the checklist
`init` helper, sets `PCSX_ALP1_OUT` to `<run-id>/frames`, writes pad edges to
`<run-id>/pad-input.tsv` (guest frame, comma-separated button names), and launches
PCSX-Redux with the framebuffer helper. If the app is not in
`/Applications`, the script prints the install steps from
[tools/pcsx/README.md](../../../tools/pcsx/README.md) and exits 2.

After the session (or to refresh the checklist file on an existing run dir):

```sh
python3 tools/alp1_observation_checklist.py init \
  build/coordination/alp1-movement-observation/<run-id>
python3 tools/alp1_observation_checklist.py show \
  build/coordination/alp1-movement-observation/<run-id>
python3 tools/alp1_observation_checklist.py validate \
  build/coordination/alp1-movement-observation/<run-id>
```

Dry-run layout check (no emulator):

```sh
python3 tools/alp1_observation_checklist.py self-test
python3 tools/alp1_observation_checklist.py validate \
  build/coordination/alp1-movement-observation/_dry_run
```

Fill `session.txt` and the row in `checklist.tsv`. Do not commit anything
under `build/coordination/`.

Progress helper (local only):

```sh
python3 tools/alp1_observation_summarize.py \
  build/coordination/alp1-movement-observation/<run-id>
```

`pad-input.tsv` only records the guest pad API. Map keyboard or a physical
controller to **pad 1** in PCSX-Redux before the compare window, or the log
stays empty while frames still capture.

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

Prefer `tools/pcsx/run_alp1_observation.sh` (see **Operator quick start**).
Manual equivalent from the repository root:

```text
-portable build/coordination/alp1-movement-observation/<run-id>/pcsx-config
-interpreter -debugger -run -iso "$AM3D_DISC"
-exec "dofile('tools/pcsx/alp1_movement_observation.lua')"
```

Leave fast boot off (do not pass `-fastboot`). Set `PCSX_ALP1_OUT` to the
run's `frames/` directory. Helper details:
[tools/pcsx/README.md](../../../tools/pcsx/README.md).

## Operator report (2026-11-21)

Uninstrumented PCSX session on the owner USA disc. No frame numbers or
`checklist.tsv` row committed from this report alone.

| Step | Result |
| --- | --- |
| Boot / intro | Operator reached the game intro, then the main menu path below. |
| `1 PLAYER` menu | Reached; **NEW GAME** was used (not the first-screen Down test). |
| Confirm **NEW GAME** | **Cross (X)** on **NEW GAME**. No second options screen after confirm. |
| Load | Roughly **5 seconds** of loading, then gameplay. |
| Difficulty / name / memory card | **None** observed between menu confirm and in-mission play. |
| Mission select | **None** observed; play went **straight into a mission**. |
| Mission id | **Unknown** on screen. Owner `MISSION.INI` sets `Bootcamp_Mission = 8` for new-player bootcamp (`Bootcamp_ID = alp`), which may **not** be the `DATA/ALP1.*` slice row 8 tests. Confirm HUD / mission name before **Reach ALP1**. |
| On-screen mission title | **None** observed after load (operator report 2026-11-21, run `20261121-095957`). Do not infer ALP1 from visuals alone. |
| Operator map guess | **Likely bootcamp** (training layout), not Alpine snow. Subjective; not a file-load proof. |
| Retail ini alignment | Owner `MISSION.INI` sets `Bootcamp_Mission = 8` and `Bootcamp_ID = alp` for new-player bootcamp. That path may load bootcamp assets, not `DATA/ALP1.*`. |
| Compare window | Not recorded (idle / Cross hold frames, spawn sanity, captures). |

Copy these answers into the active run's `session.txt` and checklist when
using `run_alp1_observation.sh`. Mark **Reach ALP1** `N` until mission id is
confirmed.

## Controller path to ALP1

High-level steps. First-screen **Down** on the menu is observed in
[first-screen-observation.md](first-screen-observation.md). The 2026-11-21
**NEW GAME → load → mission** path is recorded in the table above. Frame
timings and mission-select steps below stay open where not cited.

1. Observed boot images, from the first-screen note: Sony Computer
   Entertainment BIOS screen, PlayStation license screen, 3DO logo, Green
   Plastic News intro.
2. Observed: Return for 200 ms during the intro, then `LOADING`, then a
   stable `1 PLAYER` menu with `NEW GAME` white and `OPTIONS` gray.
3. Observed: Down for 100 ms moves the highlight from `NEW GAME` to
   `OPTIONS`. Starting a mission needs `NEW GAME` highlighted. If a run
   lands on `OPTIONS`, move back to `NEW GAME`. The exact key and duration
   for that return are TBD.
4. Observed once (2026-11-21): **Cross** confirms **NEW GAME** with no follow-up
   menu. Guest frame count and duration are not recorded.
5. Observed once (2026-11-21): **no** difficulty, name, or memory-card prompts
   before load. Slot/card state for that run is not recorded here.
6. Observed once (2026-11-21): **no** mission-select screen; load goes direct
   to a mission. Operator judges **likely bootcamp**, consistent with
   `Bootcamp_Mission = 8` in `MISSION.INI`, not proven ALP1. Row 8 host
   retail tests still target `DATA/ALP1.*` on disc; they do not prove bootcamp
   play loaded those files. Owner file header for row 8 remains `//Alpine1
   Mission1` in `ALP1.TXT`.
7. Open: guest frame when in-mission view is stable, then the eight-frame
   compare window (idle then Cross).

Stop the note at the first unknown prompt. Do not guess a button.

### Menu path worksheet (copy per run)

Record Y/N and notes in the run directory. Steps 3 to 7 stay TBD until filled.

```text
[ ] 1. Boot: SCE BIOS, PlayStation license, 3DO logo, Green Plastic News intro (observed elsewhere)
[ ] 2. Intro: Return ~200 ms -> LOADING -> stable 1 PLAYER menu (NEW GAME white)
[ ] 3. TBD: Return highlight to NEW GAME if on OPTIONS (key and duration: ____________)
[ ] 4. TBD: Confirm NEW GAME / start mission (key and duration: ____________)
[ ] 5. TBD: Difficulty, name, or memory-card prompts (record each: ____________)
[ ] 6. TBD: Mission select until Alpine 1 / ALP1 highlighted (path: ____________)
[ ] 7. TBD: Confirm mission; in-mission view stable (frame number: ____________)
```

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

### Compare window worksheet (copy per run)

Guest frame numbers from the emulator log or operator notes. The helper saves
`frame-NNNNNN.ppm` every `PCSX_ALP1_EVERY` vsyncs (default 60); mark button
edges separately in `session.txt`.

```text
Frame in-mission stable:     ________
Idle hold (4 guest frames):
  frame ___ , ___ , ___ , ___
Cross held (4 guest frames):
  frame ___ , ___ , ___ , ___
Cross up (release):          ________
Optional capture paths:      ________
On-screen position readout:  ________  (or "no on-screen position")
```

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
- On-screen mission title. If the HUD has none after load, write
  "no on-screen mission title" (observed on USA NEW GAME path).
- File reads only if a later run adds instrumentation. Until then, write
  "not instrumented".

## Checklist

Empty cells are fine until a run exists. Each run directory holds
`checklist.tsv` with this header (created by
`tools/alp1_observation_checklist.py init`):

| Run id | Date | Reach ALP1 (Y/N) | Spawn sanity vs PAD 50 / 1252 / 50 | After-sequence position notes | Capture paths |
| --- | --- | --- | --- | --- | --- |
| | | | | | |

Aggregate copies for the repo note can be pasted from `show` output. Per-run
source of truth stays under `build/coordination/alp1-movement-observation/`.

## Limits

- No game code changes in this procedure.
- Captures, logs, memory cards, and portable emulator config stay under
  `build/`. They do not go in git.
- Reaching ALP1, or saving frames, does not show that retail movement matches
  the host `z` step.
- Collision, camera, and mission gameplay remain open in the row 8 gaps.
- Without a mission title or file-read trace, **Reach ALP1** on the checklist
  stays **N** unless a later run proves `DATA/ALP1.*` loaded (instrumentation or
  a documented in-game path to Alpine mission 1).
