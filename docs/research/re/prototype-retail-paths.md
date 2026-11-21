# PROTOTYPE retail paths

Two player journeys share PCSX on the owner disc. They must not be merged in
acceptance checks. Host row 8 tests **`DATA/ALP1.*`** on disc. That is not the
same as **NEW GAME** first mission play (likely bootcamp).

## Path A: first screen and menu (PLAN orders 1–4, rows 1–2–7)

| Item | Status |
| --- | --- |
| Goal | `1 PLAYER` menu, FRONT presentation, Down highlight, native update loop |
| Observation | [first-screen-observation.md](first-screen-observation.md), [prototype-task-1.md](prototype-task-1.md) |
| Next engineering | Input table at `0x80064f14` / compare `0x41` at `0x80064f34`; see [call-80064f14.md](call-80064f14.md), [call-80064f48.md](call-80064f48.md) |
| Host tier | Rows 5–7 retail checkpoint ctests, menu smokes |

Skip intro through the observed Return path when capturing menu work. See
[PLAN.md](../../PLAN.md) prototype priorities.

## Path B: first mission after NEW GAME (row 8 observation)

| Item | Status |
| --- | --- |
| Goal | Document retail load into gameplay and optional movement compare window |
| Observation (2026-11-21) | Cross on **NEW GAME**, ~5 s load, no difficulty/memory prompts, no mission title, **likely bootcamp** map |
| ini hint | `MISSION.INI`: `Bootcamp_Mission = 8`, `Bootcamp_ID = alp` |
| ALP1 | **Not reached** on this path; checklist **Reach ALP1** stays **N** |
| Procedure | [prototype-alp1-movement-observation.md](prototype-alp1-movement-observation.md) (name kept; scope includes bootcamp) |

Disc `ctest *_retail` and `alp1_pad_spawn_retail` prove **`ALP1.PAD`** bytes only.

## Path C: Alpine 1 / ALP1 gameplay (row 8 host slice, retail path open)

| Item | Status |
| --- | --- |
| Goal | Retail play that loads `DATA/ALP1.*` and matches host eight-frame script |
| Blocker | No documented menu path to Alpine mission 1 yet |
| Next observation task | Find in-game route to Alpine campaign / mission 1, or CD/file trace proving ALP1 load |

Do not treat bootcamp captures as ALP1 evidence.

## Verification

| Command | Proves |
| --- | --- |
| `sh tools/prototype_retail_gate.sh` | Host prototype + owner disc file reads |
| `run_alp1_observation.sh` | Path B captures (local only) |
| PCSX menu captures | Path A (under `build/coordination/retail-screen/`) |

Index: [prototype-tier-index.md](prototype-tier-index.md).