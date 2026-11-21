# Prototype verification runbook

Single checklist for PROTOTYPE rows 5 through 9 CTest gates, shared
infrastructure tests, and optional SDL stakeholder captures. It does not claim
retail gameplay compare or backend adoption.

## Configure and run

The default build stays disc-free. Owner extract files stay under `build/disc/`.
Retail-named tests skip with exit code 77 when the required owner file is absent.

Prototype retail binaries run with working directory `build/`. They resolve
owner files at `disc/DATA/` (for example `disc/DATA/FRONT.TIM` and
`disc/DATA/ALP1.TXT`) after `python3 tools/disc.py` writes `build/disc/`.
Exit code 0 on a `*_retail` test means the file was present and assertions ran.

```text
cmake -S . -B build/host-sdl -DAM3D_WITH_SDL2=ON -DCMAKE_BUILD_TYPE=Release
cmake --build build/host-sdl --config Release
ctest --test-dir build/host-sdl -C Release --output-on-failure -R '^(front_tim|prototype_task_|prototype_playable_smoke_headless|test_disc_data_file_read)$'
```

On a single-configuration generator, omit `-C Release`. Rows 5 through 9 notes
below spell retail file prerequisites.

## Prototype CTest names

| CTest | Row | What it proves |
| --- | --- | --- |
| `front_tim` | 5 | Synthetic TIM bytes: `paint_front_tim`, `upload_front_tim`, bounds, and rejection paths |
| `prototype_task_5` | 5 | Same binary as `front_tim`; PROTOTYPE row 5 disc-free gate |
| `prototype_task_5_retail` | 5 | Owner `DATA/FRONT.TIM` layout, upload rectangles, and 44 by 128 paint placement |
| `test_disc_data_file_read` | 6 | Bounded `read_disc_data_file` reads, truncation, missing file, and buffer errors |
| `prototype_task_6` | 6 | Same binary as `test_disc_data_file_read`; row 6 alias plus optional ALP1.TXT probe |
| `prototype_task_7` | 7 | Four-frame menu scan tails, Down dispatch cite, disc-free menu transition |
| `prototype_task_7_retail` | 7 | Same transition with owner FRONT and `menu_submit_frame` before/after Down |
| `prototype_task_7_smoke_headless` | 7 | Golden checkpoint line from `run_prototype_task_7_menu_transition` without SDL |
| `prototype_task_7_smoke_headless_retail` | 7 | Same checkpoint with owner FRONT bytes; `has_front` token set |
| `prototype_task_8` | 8 | ALP1 fixture spawn, eight-frame script, mission handoff GPR, and `z` delta |
| `prototype_task_8_retail` | 8 | ALP1.TXT header probe plus the same movement checks with owner disc root |
| `prototype_task_8_smoke_headless` | 8 | Row 8 mission slice golden checkpoint line, disc-free |
| `prototype_task_8_smoke_headless_retail` | 8 | Same checkpoint with owner ALP1 pad spawn when TXT and PAD are present |
| `prototype_task_9` | 9 | Composed menu plus mission pipeline frame budgets and end state |
| `prototype_task_9_retail` | 9 | Full pipeline with owner ALP1.TXT header when extract is present |
| `prototype_playable_smoke_headless` | 9 | Row 9 playable pipeline checkpoint line (`8 9 1316 4 1 8 …`), no window |

## Optional SDL stakeholder capture

SDL is optional for CI. When `AM3D_WITH_SDL2=ON` and the executable is built,
stakeholders can record BMPs without a visible display:

```text
SDL_VIDEODRIVER=dummy SDL_AUDIODRIVER=dummy SDL_RENDER_DRIVER=software \
  ./build/host-sdl/am3d_prototype_playable_smoke --hidden --capture
```

With owner `disc_root/DATA/FRONT.TIM`, writes
`build/platform/prototype_playable_smoke-menu.bmp` and
`prototype_playable_smoke.bmp`. Without FRONT, writes the single diagnostic BMP.
`--checkpoint` also writes `build/platform/task9-checkpoint.txt`. Details:
[prototype-playable-smoke.md](prototype-playable-smoke.md).

A dummy-driver capture does not prove a visible window works.

## Row notes and scope

| Topic | Note |
| --- | --- |
| Row 5 | [prototype-task-5.md](prototype-task-5.md), [front-tim.md](front-tim.md) |
| Row 6 | [prototype-task-6.md](prototype-task-6.md) |
| Row 7 | [prototype-task-7.md](prototype-task-7.md), menu service inventory [prototype-task-2.md](prototype-task-2.md) |
| Row 8 | [prototype-task-8.md](prototype-task-8.md), [prototype-alp1-movement-observation.md](prototype-alp1-movement-observation.md) |
| Row 9 | [prototype-task-9.md](prototype-task-9.md), [prototype-playable-smoke.md](prototype-playable-smoke.md) |
| PsyZ row 3 | Adapter trial not started in-repo; fill sink reference unchanged. [prototype-psyZ-trial-status.md](prototype-psyZ-trial-status.md) |

Roadmap table: [PROTOTYPE.md](../../PROTOTYPE.md).

## Merge gate

Before you call prototype doc or verification work done:

```text
python3 tools/pr_guard.py
```