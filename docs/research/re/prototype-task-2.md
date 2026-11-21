# PROTOTYPE task 2 first-screen service inventory

Status: **documented** at this change. This is an observation inventory for the
`1 PLAYER` menu that [first-screen-observation.md](first-screen-observation.md)
selects. It lists only what **row 7** menu work needs. It does not claim a
native running screen, retail equivalence, or a complete machine inventory.

Row 1 observation record: [first-screen-observation.md](first-screen-observation.md).

## Screen scope

Retail anchor: PCSX-Redux on USA `SLUS-00491`, stable `1 PLAYER` menu with
`NEW GAME` / `OPTIONS`, and a visible Down transition between highlights
([first-screen-observation.md](first-screen-observation.md), row 7 cites the
same checkpoints in [prototype-task-7.md](prototype-task-7.md)).

## Files (observed or measured)

| Name | Path / lead | Cited note |
| --- | --- | --- |
| Menu texture | Owner `DATA/FRONT.TIM` (`build/disc/DATA/FRONT.TIM` in tests) | Measured layout [front-tim.md](front-tim.md); LBA 20810, length 2880 [front-tim-upload-observation.md](front-tim-upload-observation.md); `CdControl` seek to FRONT extent frame 3620 |
| Disc extract layout | `python3 tools/disc.py` → `build/disc/` | [prototype-task-5.md](prototype-task-5.md), [prototype-task-6.md](prototype-task-6.md) |
| Startup lookup string | `MEMCARD.TIM` (filename only at `0x80062e0c`) | [first-screen-observation.md](first-screen-observation.md), [deviations.md](deviations.md) |
| ISO metadata sector | Sector 16 read via wrapper; buffer `0x80119e34` | [first-screen-observation.md](first-screen-observation.md) run 7; not tied to menu pixels |
| Mission assets (not menu row 7) | `DATA/ALP1.*` | [prototype-task-8.md](prototype-task-8.md) |

FRONT.TIM byte identity at `LoadImage` entry matches owner file (2880 bytes,
zero mismatches) per [front-tim-upload-observation.md](front-tim-upload-observation.md).
Retail draw site and file-open path for that upload stay open.

## SDK and BIOS interfaces

| Service | Address / symbol | Role for row 7 menu | Cite |
| --- | --- | --- | --- |
| `PadGetState` | `0x80094fe0` | Controller status each menu frame; caller builds `a0` from stack and `s7` | [call-80064e58.md](call-80064e58.md), [call-80064e40.md](call-80064e40.md); 600 hits `a0=0`, `ra=0x80064e58` in [call-8007c11c.md](call-8007c11c.md) menu capture |
| Pad dispatch table | Words at `0x800c3e98 + s2*4` | Indirect `jr v0` after status compare | [call-80064e68.md](call-80064e68.md), [call-80064e58.md](call-80064e58.md) |
| `CdRead` / `CdReadSync` | Returns `0x8005c224` / `0x8005c238` | Eight matched pairs on first-screen path; wrapper entry `0x8005c1a0` | [first-screen-observation.md](first-screen-observation.md); [call-8005c224.md](call-8005c224.md), [call-8005c238.md](call-8005c238.md), [call-8005c1a0-2.md](call-8005c1a0-2.md) |
| Menu submit wrapper | `call_8007c11c` (`0x8007c11c`) | `DrawSync`, optional callback branch, `DrawOTag` on ordering table | [call-8007c11c.md](call-8007c11c.md), [menu-scan-submission.md](menu-scan-submission.md) |
| `DrawSync` | `0x800865c8` | First step inside submit wrapper | [call-8007c11c.md](call-8007c11c.md) |
| `DrawSyncCallback` | `0x800864d0` | Registered callback `0x8007c00c` on nonzero `gp+0x0c` path | [call-8007c11c.md](call-8007c11c.md); body lead [call-8007c00c.md](call-8007c00c.md) |
| `DrawOTag` | `0x80086bbc` | Walk ordering table; menu samples `ra=0x8007c168` | [first-screen-observation.md](first-screen-observation.md) run 8; [call-8007c11c.md](call-8007c11c.md) |
| `LoadImage` | `0x80086874` | VRAM upload during menu bucket; source lead `0x801b0974` | [first-screen-observation.md](first-screen-observation.md) runs 8–9; FRONT match [front-tim-upload-observation.md](front-tim-upload-observation.md) |

Host stand-ins for later rows (not retail recreation): `read_disc_data_file`
[row 6], `upload_front_tim` / `menu_submit_frame` [row 5, row 7 notes].

## Callback and service order

### Known (cited)

1. **Disc read wrapper (startup / metadata path):** wrapper at `0x8005c1a0`
   then `CdRead` return at `0x8005c224` then `CdReadSync` return at
   `0x8005c238`; eight matched pairs before menu frame in run 7
   ([first-screen-observation.md](first-screen-observation.md)).
2. **FRONT seek before upload:** `CdControl` seek into `DATA/FRONT.TIM`
   extent, then `LoadImage` with rectangle matching file pixel block
   ([front-tim-upload-observation.md](front-tim-upload-observation.md)).
3. **Per-frame menu submit sample (600-frame gate):** named `PadGetState`
   with `ra=0x80064e58`, then later entries to `call_8007c11c` with
   `a0`/`a1` `0x800c8518` or `0x800ca918` and `0x900`; inside the wrapper,
   `DrawSync` then load `gp+0x0c` then `DrawOTag` at computed table address
   ([call-8007c11c.md](call-8007c11c.md)). All sampled branch words were zero
   (callback branch not taken in that capture).
4. **Pad status to dispatch (index 2 samples):** compare `s2` from
   `PadGetState`, fallthrough loads word at `0x800c3ea0`, live destination
   `0x80064f14` ([call-80064e58.md](call-80064e58.md)).

### Open

| Topic | Gap |
| --- | --- |
| Full frame loop | Order of pad read, table mutation, GPU list build, and submit across a reconstructed main loop |
| `DrawSyncCallback` | Nonzero `gp+0x0c` path supported statically but not observed in menu gate ([call-8007c11c.md](call-8007c11c.md)) |
| Async CD | Whether menu FRONT bytes use the same `CdRead`/`CdReadSync` wrapper or streaming `CdControl` only |
| `PadGetState` return semantics | Sampled `v0=2` at branch; button bits and selection field not captured ([call-80064e58.md](call-80064e58.md)) |
| Index 3 dispatch | Down transition needs word at `0x800c3ea4`; retail captures kept `s2=2` while highlight moved ([call-80064e68.md](call-80064e68.md), [menu-scan-pad-sdl.md](menu-scan-pad-sdl.md)) |
| GPU packet payload | List node counts in run 11; texture contents and replay not established ([first-screen-observation.md](first-screen-observation.md) run 11) |

## Unresolved (row 7 blockers called out in table row 2)

| Item | Status | Cite |
| --- | --- | --- |
| Live word at `0x800c3ea4` | Provisional host inject only (`0x80064f14`); no retail RAM dump | [call-80064e68.md](call-80064e68.md), [prototype-task-7.md](prototype-task-7.md) |
| Full `PadGetState` | SDK entry named; body and buffer layout not reconstructed | [call-80064e58.md](call-80064e58.md), [call-80064e40.md](call-80064e40.md) |
| GPU menu loop | Partial `call_8007c11c` plus host `menu_submit_frame`; not retail scene main | [menu-scan-submission.md](menu-scan-submission.md), [native-submit-integration.md](native-submit-integration.md) |

Each unknown above has either a cited caller or a named observation task in
the linked notes. This inventory does not reopen the parked static lane at
`0x80061fe4`.

## PROTOTYPE rows 5 through 9 (downstream)

| Row | This inventory feeds | Research note |
| --- | --- | --- |
| 5 | FRONT layout and upload stand-in | [prototype-task-5.md](prototype-task-5.md), [front-tim.md](front-tim.md) |
| 6 | Sync host read boundary (not `CdRead` recreation) | [prototype-task-6.md](prototype-task-6.md) |
| 7 | Menu scan, Down dispatch, FRONT submit | [prototype-task-7.md](prototype-task-7.md), [menu-scan-smoke.md](menu-scan-smoke.md) |
| 8 | Mission load after menu (out of menu inventory) | [prototype-task-8.md](prototype-task-8.md) |
| 9 | Pipeline chains row 7 then row 8 | [prototype-task-9.md](prototype-task-9.md), [prototype-playable-smoke.md](prototype-playable-smoke.md) |