# Faster path to a working prototype

Reviewed November 16, 2026, at local commit 5833a8c. This is a roadmap
change and an online source review. It does not close a game gap, import
code, or record an executed backend trial. [PLAN.md](PLAN.md) is the roadmap.

## Decision

Make one observed front-end screen run from our code before widening the
decomp. Keep compiler calibration as supporting research. Reuse a tested
PS1 graphics implementation if a small adapter passes our required checks.
Do not write a full GPU, GTE, SPU, and CD runtime before testing that option.

The recommended order is retail observation, graphics trial, one file and
texture path, one screen loop, then one mission. Each change still closes
one gap or replaces one stand-in under AGENTS.md.

## What exists now

- `python3 tools/progress.py` reports 1,869 inventoried functions, three
  implemented functions, and zero verified functions in the evidence ledger.
  This is recorded evidence coverage, not a complete audit of all source.
- There are 735 C++ files under components/exe/. Many are partial blocks.
  246 of those files contain gap comments. File counts do not establish
  whole-function behavior or a connected program.
- src/main.cpp extracts the disc and inspects the executable, then exits.
  It does not call a reconstructed game main loop.
- src/platform_smoke.cpp runs its own loop. It clears and swaps buffers,
  decodes FRONT.TIM directly into pixels, draws a marker, and polls input.
  The image is placed at a host-selected position. This is not retail
  texture submission or a retail scene.
- The current GPU sink accepts fill packets only. It rejects other GPU
  commands. Disc callbacks, textured drawing, geometry, audio, movies, and
  the retail scene loop remain open. See [PLATFORM.md](PLATFORM.md).
- The parked static boot and the observed retail MEMCARD path have different
  backup-count state. Existing notes already identify this difference.
  See [deviations.md](research/re/deviations.md). Keep both records intact.

The planning inference is that connecting a narrow slice now has more
prototype value than adding unrelated block implementations or tuning the
compiler. The earlier scanner speed measurements already put those tools
well below the cost of preparing and reviewing a note.

## Existing implementations worth using

These are source-reviewed candidates and patterns. No upstream project
proves that Army Men runs with its backend. Pins below identify the review,
not an approved dependency update.

### PsyZ: first graphics trial

Reviewed revision: `3413eeb8cd16bfcc3c5a7041bd1392b31bc1c5cc`.

Concrete files:

- [libgpu.c](https://github.com/Xeeynamo/psyz/blob/3413eeb8cd16bfcc3c5a7041bd1392b31bc1c5cc/psyz/src/psyz/libgpu.c)
  dispatches opcode 0x02, walks primitive lists, and routes SDK image loads
  to a drawing backend. This addresses a specific hole in our earlier
  PsyCross trial.
- [sdl3_software.c](https://github.com/Xeeynamo/psyz/blob/3413eeb8cd16bfcc3c5a7041bd1392b31bc1c5cc/psyz/src/platform/sdl3_software.c)
  implements VRAM image upload and primitive submission through its renderer
  interface. Trial the software renderer first to simplify pixel checks.
- [libgte.c](https://github.com/Xeeynamo/psyz/blob/3413eeb8cd16bfcc3c5a7041bd1392b31bc1c5cc/psyz/src/psyz/libgte.c)
  supplies geometry operations. Evaluate the needed subset when the mission
  slice identifies its calls. Do not port it speculatively for a 2D screen.
- [libcd.c](https://github.com/Xeeynamo/psyz/blob/3413eeb8cd16bfcc3c5a7041bd1392b31bc1c5cc/psyz/src/psyz/libcd.c)
  exposes disc-path and read-callback hooks. These are candidates for a
  later disc boundary, not a source for Army Men's file parser.

Important limits: the raw GPU image-write and image-read handlers in
libgpu.c are stubs. The SDK image-load path is separate. A successful
LoadImage test does not establish raw GP0 transfer support. Record which
path the game uses. The upstream README also favors API compatibility
over exact hardware behavior, so retain our retail quirks and checks.

The [porting guide](https://github.com/Xeeynamo/psyz/blob/3413eeb8cd16bfcc3c5a7041bd1392b31bc1c5cc/PORTING_GUIDE.md)
explains host-sized primitive tags and ordering tables. Marshal our fixed
32-bit packet words into the backend's types. Do not reinterpret a retail
packet as a native pointer list or widen every game word to hold pointers.

The [CMake build](https://github.com/Xeeynamo/psyz/blob/3413eeb8cd16bfcc3c5a7041bd1392b31bc1c5cc/psyz/CMakeLists.txt)
uses SDL3 and multiple SDK implementation files. Keep that dependency in
an optional trial target. The existing SDL2 smoke target stays buildable.
The README's root make setup downloads a proprietary SDK for console
cross-compilation. That setup is not needed for this native-only trial
and must not be run here.

The [root license inventory](https://github.com/Xeeynamo/psyz/blob/3413eeb8cd16bfcc3c5a7041bd1392b31bc1c5cc/LICENSE)
assigns MPL-2.0 to platform and psyz implementation directories and marks
the include directory and src/psyq unlicensed. The
[decomp subtree](https://github.com/Xeeynamo/psyz/blob/3413eeb8cd16bfcc3c5a7041bd1392b31bc1c5cc/decomp/LICENSE)
has a separate MIT notice. Do not label the entire project MIT or adopt
the full header tree without resolving its grant. Trial locally first.
Any import needs a selected-file and dependency inventory with notices.

### SOTN: native entry and repeatable input

Reviewed revision: `3a0957bee537554b08e830413f3ae2572b552e6e`.

Its [native initialization](https://github.com/Xeeynamo/sotn-decomp/blob/3a0957bee537554b08e830413f3ae2572b552e6e/src/pc/sotn.c)
connects the game callback to PsyZ and supplies a disc path. This is a
concrete example of a native port boundary beyond the matching workflow
already studied here. Our equivalent should connect an observed screen
update to host services without embedding host setup in game functions.

Its [replay implementation](https://github.com/Xeeynamo/sotn-decomp/blob/3a0957bee537554b08e830413f3ae2572b552e6e/src/pc/replay.c)
records controller frames, initial state, and selected state for drift
checks. Adapt the method: record frame-indexed inputs and a small set of
Army Men state checks supported by our notes. Do not copy its save format,
game state, or reconstructed gameplay.

### REDRIVER2: narrow host startup

Reviewed revision: `b2d8857426f815007486def9bd23f9a6007a2c64`.

Its [host entry](https://github.com/OpenDriver2/REDRIVER2/blob/b2d8857426f815007486def9bd23f9a6007a2c64/src_rebuild/redriver2_psxpc.cpp)
initializes PsyCross, optionally attaches a CD image, calls the game entry,
and shuts down the host. Adopt that separation as a design pattern.
Do not transplant Driver logic or reopen our stopped PsyCross build trial
without a specific new fix. Its pinned PsyCross submodule is the revision
already evaluated in [PLATFORM.md](PLATFORM.md).

### PS1Recomp: bounded local execution experiment

Reviewed revision: `49c4a5164149a0b0eeaf1299f7cffa56d5ee1df1`.

The [project](https://github.com/PS1Recomp/ps1-recomp/tree/49c4a5164149a0b0eeaf1299f7cffa56d5ee1df1)
generates C++ from MIPS and supplies a PS1 runtime. Its documented validated
title is Crash Bandicoot. New games need their own function and runtime
facts. Army Men support is untested in this review.

Concrete implementation leads are its
[GPU command parser](https://github.com/PS1Recomp/ps1-recomp/blob/49c4a5164149a0b0eeaf1299f7cffa56d5ee1df1/ps1Runtime/src/gpu/gpu.cpp),
[SDK GPU calls](https://github.com/PS1Recomp/ps1-recomp/blob/49c4a5164149a0b0eeaf1299f7cffa56d5ee1df1/ps1Runtime/src/psyq/psyq_libgpu.cpp),
and [address dispatcher](https://github.com/PS1Recomp/ps1-recomp/blob/49c4a5164149a0b0eeaf1299f7cffa56d5ee1df1/ps1Recomp/src/dispatch_emitter.cpp).
The dispatcher suggests a possible function-replacement boundary. A bridge
from its register/RAM context to our typed functions would still need work.
Its SDK calls include Crash-specific assumptions that need checking here.
The selected root license declares GPL-3.0-or-later.

If tried, allocate one local work session to a synthetic execution check
and an initial owned-disc boot attempt. Keep all generated game C++, logs,
and data under build/. Check delay-slot behavior, indirect calls, missing
targets, and required overlays. Record the last reached retail milestone
and the first concrete failure. A successful build using its no-game stub
is not a boot. Stop after three failures at the same problem.

Continue only if the trial reaches a useful observed boundary or produces
a small, credible fix list. Otherwise park it. A generated runtime can be
a prototype aid, but is not our decomp or a verified source implementation.
Do not combine it with a second backend migration in the same change.

## Ordered work and acceptance checks

These are ordered tasks, not promised completion dates. Unknown formats
and callbacks prevent a reliable date for the first playable mission.

| Order | Focused work | Acceptance check |
| --- | --- | --- |
| 1 | Define the first screen from retail observation. Use the existing PCSX-Redux capture setup. | Record executable and emulator identity, boot mode, memory-card state, and exact controller steps. Identify one displayed frame, its asset reads, GPU submission, and a controller-driven transition. Keep captures local. |
| 2 | Inventory only that screen's required services. | List called SDK/BIOS interfaces, callback order, file names, packet types, and unresolved game calls. Each unknown has a cited caller or an explicit observation task. Do not inventory the whole machine again. |
| 3 | Trial the PsyZ adapter with original synthetic inputs. | Check the existing fill quirks, draw/display page changes, a 4-bit texture and palette upload, a textured rectangle, clipping, transparency used by the screen, and controller press/release. Raw GPU transfers are a separate check if observed. |
| 4 | Decide whether to adopt selected backend files. | Record exact files, revision, dependencies, license grants, and Mac/Windows/Linux build results. Record untested hosts explicitly. Stop the trial at three failures on the same problem. If blocked, test a narrower licensed component or PS1Recomp's GPU behind the same boundary in a separate trial. |
| 5 | Replace one image stand-in through the observed upload path. | Select FRONT.TIM or another observed file. Our parser comes from its measured layout. Use measured retail placement and palette; preserve the disc-free fallback. A decoded image still does not count as a running scene. |
| 6 | Close one required file-read or callback gap per change. | Synthetic tests check bytes, bounds, callback order, and completion/error behavior. Local retail evidence checks actual names, sizes, and state. Preserve observed asynchronous behavior rather than inventing immediate success. |
| 7 | Connect the selected screen's update loop and controller transition. | A fresh native run reconstructs the screen from the owner's files. Our update code produces multiple frames and the observed input transition. Compare against retail at named checkpoints. Captured packet replay alone does not pass. |
| 8 | Load one mission and implement one movement sequence. | Declare start state and fixed input frames. Check movement, camera, collision, and the resulting state against retail. Add only the graphics, geometry, audio, or movie services this sequence reaches. |
| 9 | Chain the menu transition into one mission movement run. | One host pipeline runs the row 7 menu scan and controller transition, records mission load intent, then executes the row 8 fixed movement script. `ctest prototype_task_9` passes disc-free; `prototype_task_9_retail` when ALP1.TXT is present. Checkpoint smoke writes stage counts and end state. Captured menu replay or mission frames alone do not pass. No retail in-mission boot required at this row. |

Tasks 1 and 2 are observation work. Task 3 is a tooling/backend trial.
Tasks 5 through 9 are milestones split into one-gap implementation changes,
each with its own required research note. The table is not permission to
bundle several gaps into one change or bypass note boundaries.

### Rows 1 and 2 (observation tier)

| Row | Tier status | Research note |
| --- | --- | --- |
| 1 | PCSX-Redux `1 PLAYER` menu, Down highlight transition, bounded CD/GPU traces | [first-screen-observation.md](research/re/first-screen-observation.md) |
| 2 | Row 7 menu service inventory (files, SDK cites, callback order, open gaps) | [prototype-task-2.md](research/re/prototype-task-2.md) |

### Rows 5 and 6 (retail checkpoint tier)

| Row | Tier status | Research note |
| --- | --- | --- |
| 5 | FRONT.TIM measured layout, `upload_front_tim`, disc-free fallback | [prototype-task-5.md](research/re/prototype-task-5.md), [front-tim.md](research/re/front-tim.md) |
| 6 | `read_disc_data_file` bounds; ALP1.TXT probe on row 8 slice | [prototype-task-6.md](research/re/prototype-task-6.md) |

### Rows 7 through 9 (retail checkpoint tier)

These rows have a documented **retail checkpoint tier** on native builds. It
names before/after controller transitions, headless ctests, and owner-file
smokes. It does not claim pixel-identical retail menus, reconstructed game
main, or in-mission physics match. Full table acceptance in rows 7 and 8 still
needs retail compare beyond named checkpoints.

| Row | Tier status | Research note |
| --- | --- | --- |
| 7 | Menu scan, Down dispatch, FRONT submit, selection highlight stand-in | [prototype-task-7.md](research/re/prototype-task-7.md) |
| 8 | ALP1 spawn from PAD fixture, eight-frame movement, observation runbook | [prototype-task-8.md](research/re/prototype-task-8.md), [prototype-alp1-movement-observation.md](research/re/prototype-alp1-movement-observation.md) |
| 9 | Pipeline composes row 7 then row 8 runners; playable smoke with FRONT | [prototype-task-9.md](research/re/prototype-task-9.md), [prototype-playable-smoke.md](research/re/prototype-playable-smoke.md) |

Use the first two changes for the screen observation record and the
synthetic graphics trial. Do not start with another compiler experiment.
During the trial, retain the current fill sink as a small reference for
already checked behavior. If the trial cannot resolve its dependency or
license scope, keep the existing window and advance one observed service
at a time instead of starting a full hardware rewrite.

## Measures of useful progress

Track screens reached from fresh startup, required interfaces connected,
the first failing call, repeated-input drift, and retail comparison results.
Track per-frame time only after a real update loop runs. Keep the function
ledger honest and separate from these integration results.

A local frame replay can test a renderer. A loader test can check bytes.
An emulator can provide a behavior reference. None proves that our native
game update loop runs. The first-screen exit requires that loop and one
observed controller transition. The playable exit requires the declared
mission sequence.

Do not reopen the parked static branch, add a full segment-map project,
reinstall existing analysis tools, or optimize compiler scheduling to claim
prototype progress. Continue those only when the selected slice exposes a
specific need. Keyboard play, network browsing, and mods remain later work.

Run the checks relevant to each change and `python3 tools/pr_guard.py`.
Keep the default disc-free build and the existing platform test working.
Retail captures and generated source stay local. Ask before any issue,
pull request, or push.
