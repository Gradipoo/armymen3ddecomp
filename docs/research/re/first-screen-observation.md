# First screen observation

Status: preliminary. Two retail emulator runs displayed a `1 PLAYER` menu
and an input was followed by a visible selection change. This is a candidate
first screen for [PROTOTYPE.md](../../PROTOTYPE.md). Its required services
and a running native screen remain unverified.

## Retail observation

On November 16, 2026, PCSX-Redux booted the USA disc, serial SLUS-00491,
with interpreter execution and fast boot disabled. Its log reported the disc
ID `SLUS00491` and BIOS `8d8cb7e4`, labeled SCPH-7003 (US). A task-local
copy of the app supplied a bundle identifier for window access. Its binary
identity and the launch record stay under `build/coordination/retail-screen/`.
The bundled version record identifies dev build 443, version `7637751d`.
Its source revision has not been independently verified against the binary.
The separately extracted executable identity is recorded locally; the run
log names the disc executable but does not independently verify that extract
against the current disc image.

The first run created and loaded two task-local memory-card files. The repeat
started from preserved matching initial card copies. Saved configuration for
the repeat records both slots inserted, the first pad connected and the
second disconnected, with the same pad settings as the preceding run. Card
contents, guest-visible device state, and the meaning of the numeric controller
type were not verified. Subsequent card saves changed the working files.

The observed sequence was the Sony Computer Entertainment BIOS screen,
PlayStation license screen, 3DO logo animation, and Green Plastic News intro.
During the intro, the operator pressed and released Return for 200 ms. The
next observed image was `LOADING`, followed by a stable `1 PLAYER` menu with
`NEW GAME` white and `OPTIONS` gray. At that menu the operator pressed and
released Down for 100 ms. The next image showed `OPTIONS` white and
`NEW GAME` gray. No other host game key was sent. This supports a visible
menu navigation transition. The run did not isolate whether Return caused
the intro to end. A later clean run repeated the same two host inputs at those
checkpoints and the same visible selection change. This is not a pixel-exact
comparison.

The repeat saved framebuffer captures every 60 guest vsyncs. The inspected
`build/coordination/retail-screen/run5/menu-before.png` comes from
`frames/frame-003720.bmp` and shows `NEW GAME` white. The inspected
`menu-after.png` comes from `frames/frame-005040.bmp` and shows `OPTIONS`
white. These capture counters do not establish the exact input edge frames.
There are no input-read traces. Screen-specific file reads, image uploads,
GPU submissions, callbacks, and timing remain unknown. This observation does
not show a reconstructed native update loop.

## Bounded service observation

A later instrumented run used the same preserved initial card state and
reached the `1 PLAYER` menu. The inspected local capture
`build/coordination/retail-screen/run6/menu-before.png` comes from frame
4800 and shows `NEW GAME` white. The trace recorded one lookup at frame 1654:
the argument began `MEMCARD.TIM` and the return address was `0x80065998`.
This lookup alone does not associate that file with the menu.

The trace recorded eight returns at `0x8005c224`, each with `v0` 1, and
eight at `0x8005c238`, each with `v0` 0. See the cited caller and return
notes [call-8005c224.md](call-8005c224.md) and
[call-8005c238.md](call-8005c238.md). Seven pairs occurred during startup.
The last recorded read return was at frame 3257 and the sync return at frame
3265, with `s1` `0x80119e34`. They preceded the retained menu frame. The
trace did not record a filename for that read, so its destination and timing
alone do not identify a menu asset.

The last trace checkpoint at frame 3600 reported no callback errors. The
process stopped manually before its 7200-frame budget and did not emit final
counters. The last saved capture was frame 5940. This is not a full-budget
negative result or a complete inventory. A later Down input was followed by
`LOADING DEMO`; idle timeout timing was not isolated, so that input is not
counted as a repeated navigation transition. The clean run 5 transition above
remains the repeat evidence. No image upload, GPU submission, or callback
trace was collected for this run.

## Matched read request

A further instrumented run reached the `1 PLAYER` menu with `NEW GAME`
selected. The inspected `build/coordination/retail-screen/run7/menu.png`
comes from frame 4560. The only host game input was Return for 200 ms during
the intro. The process stopped manually before its 7200-frame budget, so this
is not a full-budget negative result.

The trace matched eight wrapper entries at `0x8005c1a0` with eight `CdRead`
returns at `0x8005c224` and eight `CdReadSync` returns at `0x8005c238`.
It reported no errors or mismatches. The last entry was id 8 at frame 3050:
`a0` `0x80119e34`, `a1` `0x10`, `a2` 1, `ra` `0x8005c94c`, and `sp`
`0x80010a8c`. Its read return at frame 3050 had `v0` 1; its sync return at
frame 3058 had `v0` 0. The saved caller matched `0x8005c94c` at `sp+0x20`,
as recorded in [call-8005c1a0-2.md](call-8005c1a0-2.md).

A local check of the owner's disc found sector 16 is an ISO 9660 primary
volume descriptor, with a 2048-byte logical block and a root record at LBA
22 of length 2048. The request is consistent with a metadata read, not evidence
of a menu image. The post-read buffer was not compared with that sector. This
run does not establish whether other reads occurred or assets were preloaded.
No image upload or GPU submission was captured.

## Bounded graphics observation

A later instrumented run retained `build/coordination/retail-screen/run8/menu.png`
from frame 4320. It shows `1 PLAYER` with `NEW GAME` selected. The only host
game input was Return for 200 ms during the intro. The process stopped manually
with exit 255 and no final summary. The last complete bucket ends at frame
4320. One retained frame does not establish the screen for that whole bucket.

For frames 4260 to 4320, the trace counted 60 `LoadImage` entries at SDK
`0x80086874`, all arriving with `ra` `0x8005e270`. Four retained samples had
raw `a0` `0x80010acc`, `a1` `0x801b0974`, and `a2` and `a3` 0. The trace
also counted 60 `DrawOTag` entries at SDK `0x80086bbc`, all arriving with
`ra` `0x8007c168`. Four sampled `a0` values alternated between `0x800ccd14`
and `0x800ca914`. `DrawPrim` had zero entries in this bucket. Samples were
capped at four per caller per bucket and do not describe every call.

Through frame 4320, the totals were 7441 `LoadImage`, 10 `DrawPrim`, and
1205 `DrawOTag` entries. Complete checkpoints reported zero callback errors,
and bucket and cumulative summaries reported zero caller overflow. No SDK
body was entered and no rectangle, image, list, or packet data was read.
These observations do not identify an asset or establish a native update loop.

## Bounded rectangle observation

Run 9 was captured on November 16, 2026 and reviewed on November 17. It
reached the `1 PLAYER` menu; the retained `menu-004200.png`, converted from
`frames/frame-004200.bmp`, was visually checked by the principal and shows
`NEW GAME` selected. The 4200-frame budget ended with final counters: 1161
targeted `LoadImage` entries at SDK `0x80086874` arriving with caller return
address `0x8005e270`. There were 40 retained rectangle samples, no sample
overflow, and an observation error counter of zero.

Using the four-halfword layout in the pinned compatibility header
`build/platform/source/PsyCross-e56e4cde1c2b8a15e0d4e38b26cdd9202e0d17e6/include/psx/libgpu.h`
at lines 323 and 827, the samples decode as raw `RECT16` values
`[0, 0, 512, 240]` and `[0, 240, 512, 240]`. The source pointer was
`0x801b0974`. The conservative width-times-height-times-two extent is
245760 bytes for each sample and fits direct RAM. The header is compatibility
evidence only, not independent proof of the retail ABI. No source pixel bytes
were read. These values do not establish the asset identity, bit depth,
visible placement, or successful upload.

Measurement and cleanup outcomes are separate. The final measurement summary
was retained, but cleanup failed afterward because `PCSX.removeBreakpoint`
was unavailable. This is not an overall tool pass. On next-day resume the
process was gone; its exact exit status was not retained. Run 9 only observed
this `LoadImage` caller and does not establish a complete graphics trace.
Evidence remains under `build/coordination/retail-screen/run9/`.

## Cleanup API check

Run 10 used no disc; the owned BIOS drove vsync. The frame-budget stop at
frame 60 removed the breakpoint through the corrected `bp:remove` path, then
continued to frame 120 and exited with code 0. Stderr was empty. This validates
the cleanup API on this no-disc frame-budget path only. It does not validate a
retail capture or callback-error path. Local evidence is under
`build/coordination/retail-screen/run10/`.

## Bounded menu-exit packet observation

Run 11 captured one bounded `DrawOTag` list during the menu exit animation.
The retained frame 4920 showed `1 PLAYER` with `NEW GAME` selected. At frame
4974, the hook at PC `0x80086bbc` arrived with caller return `0x8007c168` and
`a0=0x800ccd14`. The bounded walk reached its terminator after 2798 nodes and
2455 payload words: 2304 empty nodes and 494 nonempty nodes. An offline check
validated links, bounds, and counts. No capture errors were recorded; stderr
was empty and the clean stop message was present. After the frame 4980 capture,
the principal stopped the process with Ctrl-C (exit 255). The later image shows
menu letters rotating or flying out, so this is an exit-transition list, not a
stable-menu sample.

The recorded first-word high bytes were 469 `0x28` starts, 21 `0x20` starts,
two `0x2e` starts, one `0x80` start, and one `0x00` start. With the pinned
compatibility header
`build/platform/source/PsyCross-e56e4cde1c2b8a15e0d4e38b26cdd9202e0d17e6/include/psx/libgpu.h`
as a layout lead, the first three groups correspond to five-word flat quads,
four-word flat triangles, and nine-word semi-transparent textured quads.
This compatibility layout is not independent proof of the retail ABI. The
GP0 high-byte `0x80` four-word first command matches the VRAM-to-VRAM copy
form in the [GPU Command Summary and VRAM-to-VRAM blitting sections](https://psx-spx.consoledev.net/graphicsprocessingunitgpu/).
The single `0x00` start remains unresolved. These start counts are not a
complete GP0 command inventory. The observation does not establish texture
contents, file identity, replay correctness, or a native update loop.
Evidence, raw bytes, and hashes remain under
`build/coordination/retail-screen/run11/`.

## Earlier leads

[deviations.md](deviations.md) records retail runs with fast boot and without
fast boot. In each, `0x80062e0c` was entered once with `a0` at a string
beginning `MEMCARD.TIM` and the backup count word at `0x800dd6e8` was
`0x1ce`. The local logs are `build/research/behavior/backup-path-80062e0c.jsonl`
and `build/research/behavior/retail-addr0-beq-80061fe4.jsonl`. This is a
filename lookup lead. It does not establish a completed read or an asset of
the observed menu.

A separate startup capture used PCSX-Redux in interpreter mode, fast boot,
the USA cue, and the same reported BIOS identity. The capture at `CdReadSync`
return is `build/research/behavior/cdreadsync-8005c238-5501.jsonl`; see
[call-8005c238.md](call-8005c238.md). It does not connect that service to
the menu. The parked static branch at `0x80061fe4` remains separate under
[deviations.md](deviations.md).

## Next observation

Verify effective controller type and bindings, both slots' state, and exact
guest input edges in a later capture. The repeated visual transition does not
establish those details.

The run 10 runtime frame-budget cleanup check passed within its no-disc scope.
The run 11 list is an exit-animation capture; a stable-menu comparison remains
open. The [first PsyZ synthetic trial](psyz-synthetic-trial.md) passed eight narrow
renderer pixel checks but failed fill alignment and left required header
licenses unresolved. It did not execute SDK dispatch or visible output.
A later graphics adapter trial still needs original
synthetic inputs for fixed 32-bit list links and empty tags, flat triangles
and quads, textured quads with palette/page and semi-transparency state,
and VRAM image upload and copy. Follow the existing license and dependency
review requirements in [PROTOTYPE.md](../../PROTOTYPE.md) before considering
adoption. The meaning of GP0 `0x00` and whole-list coverage remain open. The
last matched sector 16 request is a metadata lead, not a menu asset lead.
Trace relevant callbacks and timing, tie events to a caller or frame
checkpoint, and mark missing events unknown. Keep captures and traces under
`build/`. A running native screen still requires reconstructed update code
to produce multiple frames and the observed transition.
