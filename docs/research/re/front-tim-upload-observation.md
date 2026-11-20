# FRONT.TIM upload identity

## Outcome

On November 20, 2026, identify one file used during preparation of the
observed `1 PLAYER` menu. A live RAM comparison at SDK `LoadImage` matched
all 2880 bytes of the owner's `DATA/FRONT.TIM`. The header and pixel data
had zero mismatches. This establishes the file's byte identity at upload
entry and selects a concrete native texture-upload connection.

It does not establish the file-read implementation, upload completion,
on-screen placement, or a reconstructed menu update loop.

## Sector and upload lead

The preceding bounded trace reached frame 4800 with eight matched wrapper
reads, zero errors, zero overflow, and no open tracked request. All eight
wrapper reads were descriptor or directory metadata. The trace also found
a separate streaming control path, rather than another asset read through
that wrapper. Callback registration events were not callback executions.

A bounded ISO lookup used only sectors already observed being read: 16,
22, and 398 through 408. Directory records were validated with the existing
disc reader. Of 23 recorded Setloc positions, 15 fell within file extents
and eight within descriptor or directory ranges. Extent membership is a
seek identification, not read completion.

At frame 3620, SDK `CdControl` arrived with `a0=2`, `a1=0x800e1548`,
`a2=0`, and return address `0x80074ba8`. Its three position bytes decode
to MSF `04:39:36`, LBA 20811. This lies in `DATA/FRONT.TIM`, whose extent
starts at LBA 20810 and has length 2880. The fourth parameter byte has no
established meaning here. Another `CdControl` entry that frame used
`a0=6`, `a1=0x800e1548`, `a2=0`, return `0x80074afc`.

At frame 3622, `LoadImage` arrived from return `0x8008aac0`, source
`0x80119e74`, rectangle `(640,0,11,128)`. Those dimensions and coordinates
match the file's pixel rectangle at offset 56. The palette rectangle
`(512,506,16,1)` also appeared, but its 21 calls were grouped across frames
3602 through 3626 and do not identify a specific palette submission.
These observations selected the next byte comparison; timing and rectangles
alone were not treated as identity proof.

## Live identity check

A separate isolated run used the same local observer executable and fresh
copies of the preserved initial cards. The principal observed Sony BIOS,
then Green Plastic News, pressed Return for 200 ms, and observed the
`1 PLAYER` menu with `NEW GAME` selected. The retained frame 4260 was
inspected and shows that selection. Host key duration is not an exact
guest input-edge measurement.

At frame 2873, the `LoadImage` entry from return `0x8008aac0` had source
`0x80119e74` and rectangle `(640,0,11,128)`. The probe derived base
`0x80119e34` from the file's measured pixel offset 64, validated the RAM
range, and compared every byte with the local owner file. All 64 header
bytes and 2816 pixel bytes matched. No compared asset bytes were emitted.
The reference SHA-256 is
`0d68ef7d6d1a4ae19a2aba63ae3990709f0030d85c2519fe79d795614d48d1a1`.
See the measured [file layout](front-tim.md).

The hook stopped on its first match with zero errors. Stderr was empty.
The listener cleanup path ran and the breakpoint callback returned false;
no independent removal probe was made. The principal stopped the process
with Ctrl-C, exit 255, before the independent screenshot budget. This was
not a full-budget pass.

## Evidence and next connection

Runtime manifests, exact arguments, input steps, scripts, card and source
hashes, metadata lookup, comparison record, and retained frames stay under
`build/coordination/menu-asset-path/`, with the identity run in
`front-identity/`. Game files remain local. No executable disassembly or
new SDK body investigation was needed. The repository guard passed.

The next implementation is an original native FRONT.TIM uploader that
submits its measured palette and packed pixel blocks, preserving packed
16-bit words. Keep synthetic public tests and the existing disc-free
fallback. The current smoke window's decoded-image placement is still a
stand-in; this observation does not justify replacing it with guessed
menu geometry. No game function status changes.
