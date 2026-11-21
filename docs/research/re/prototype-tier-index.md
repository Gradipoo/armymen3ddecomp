# PROTOTYPE tier index (rows 1 through 9)

Quick map from roadmap row to tier name and primary research note. CTest names
and owner-file gates live in
[prototype-verification-runbook.md](prototype-verification-runbook.md).
Roadmap table: [PROTOTYPE.md](../../PROTOTYPE.md).

| Row | Tier | Primary note |
| --- | --- | --- |
| 1 | Observation | [prototype-task-1.md](prototype-task-1.md) (detail: [first-screen-observation.md](first-screen-observation.md)) |
| 2 | Observation | [prototype-task-2.md](prototype-task-2.md) |
| 3 | Trial | [prototype-psyZ-trial-status.md](prototype-psyZ-trial-status.md) |
| 4 | Trial | [prototype-replay-trial-status.md](prototype-replay-trial-status.md) |
| 5 | Retail checkpoint | [prototype-task-5.md](prototype-task-5.md), [front-tim.md](front-tim.md). Owner FRONT via `platform::load_front_tim_disc_bytes` (`disc_front_tim_load.hpp`). |
| 6 | Retail checkpoint | [prototype-task-6.md](prototype-task-6.md) |
| 7 | Retail checkpoint | [prototype-task-7.md](prototype-task-7.md). Disc-backed menu smoke uses the same `load_front_tim_disc_bytes` path as row 5. |
| 8 | Retail checkpoint | [prototype-task-8.md](prototype-task-8.md), [prototype-alp1-movement-observation.md](prototype-alp1-movement-observation.md) |
| 9 | Retail checkpoint | [prototype-task-9.md](prototype-task-9.md), [prototype-playable-smoke.md](prototype-playable-smoke.md). Pipeline and SDL smoke load FRONT through `load_front_tim_disc_bytes` when the owner file is present. |