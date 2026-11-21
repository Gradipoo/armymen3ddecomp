# PROTOTYPE row 3 PsyZ adapter trial status

Status: **not started** as an executed trial in this repository. This note
records row 3 scope and pointers. It does not import PsyZ, change CMake, or
claim backend adoption.

Roadmap acceptance text: [PROTOTYPE.md](../../PROTOTYPE.md) ordered table,
row 3. PsyZ revision and file pins: same document, section **PsyZ: first
graphics trial**.

## Row 3 acceptance checklist

Trial the PsyZ adapter with original synthetic inputs. Each item must pass
before row 3 counts as done. All items remain unchecked.

- [ ] Existing fill quirks match the reference fill sink behavior.
- [ ] Draw and display page changes.
- [ ] 4-bit texture and palette upload.
- [ ] Textured rectangle.
- [ ] Clipping.
- [ ] Transparency used by the first observed screen.
- [ ] Controller press and release.
- [ ] Raw GPU transfers (separate check only if observed for that screen).

## Related executed and platform notes

These are earlier or parallel work. They do not close row 3 as defined above.

| Topic | Note |
| --- | --- |
| Bounded list and textured-quad adapter | [gpu-list-adapter-trial.md](gpu-list-adapter-trial.md) |
| Native FRONT.TIM draw path (PS1Recomp candidate) | [native-front-draw-trial.md](native-front-draw-trial.md) |
| SDL2 fill sink, display advance, smoke targets | [PLATFORM.md](../../PLATFORM.md) |
| Narrow PsyZ renderer coordination trial | [psyz-synthetic-trial.md](psyz-synthetic-trial.md) |

During any PsyZ adapter trial, retain the current synthetic fill sink in
[PLATFORM.md](../../PLATFORM.md) as the small reference for already checked
fill behavior. Do not drop that reference to force a migration.

## Execution state in this repo

A **narrow coordination trial** ran November 17, 2026 and is recorded in
[psyz-synthetic-trial.md](psyz-synthetic-trial.md). It is not the full row 3
in-tree adapter. Evidence stays under `build/coordination/psyz-trial/` when
present locally.

| Row 3 checklist item | Coordination trial result |
| --- | --- |
| Fill quirks vs fill sink | **Failed** alignment on a synthetic GP0-style rectangle; see psyz-synthetic-trial fill section |
| Draw and display page changes | Not executed in that runner |
| 4-bit texture and palette upload | Narrow sample **passed** in runner (not retail path) |
| Textured rectangle | **Passed** in runner |
| Clipping | **Passed** in runner |
| Transparency (first screen) | Semi-transparent 4-bit sample **passed** in runner |
| Controller press and release | Not executed |
| Raw GPU transfers | Not executed |

No PsyZ source import, optional trial target, or CMake option ships on the
default build path. Row 3 stays **open** until an in-tree adapter trial hits
the full checklist or is parked with cited failure.

Row 4 (adopt or stop) stays **open** until row 3 executes fully or is parked.

Fill retry scope and stop rules:
[prototype-psyZ-fill-retry-plan.md](prototype-psyZ-fill-retry-plan.md).

## Stop rules

Stop the trial after **three failures at the same problem**. Record what was
tried, what was learned, and the next bounded outcome.

If **license scope** for selected PsyZ files and transitive headers cannot be
resolved for the intended import, stop the adoption path. Keep the existing
SDL2 window and advance one observed service at a time. See the license
inventory in [PROTOTYPE.md](../../PROTOTYPE.md) under PsyZ pins and row 4.

Do not run the upstream proprietary SDK download or root make setup described
in the PsyZ readme. This project stays native-only for trial work.