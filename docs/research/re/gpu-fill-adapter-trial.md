# Shared VRAM fill adapter trial

## Outcome and acceptance

On November 17, 2026, test an original local adapter that keeps our fill
behavior in the isolated PS1Recomp GPU's VRAM. Require alignment, width
rounding, coordinate and size masks, wrap, RGB555 conversion, zero-size
behavior, and preservation of texture mask bits outside the fill. Retain
the three passing primitive samples from the
[previous trial](ps1recomp-gpu-trial.md).

The final runner passed 26 assertions and exited zero. This is a local
correctness trial. No backend is adopted. No game function status changes.

## Boundary

The adapter accepts one complete command per call, as fixed 32-bit words.
It validates exact lengths before touching the parser. Its supported
opcodes are fill `0x02`, flat triangle `0x20`, flat quad `0x28`, raw
semi-transparent textured quad `0x2f`, and bounded CPU-to-VRAM upload
`0xa0`. Other commands are rejected. Uploads require nonzero dimensions
at most 1024 by 512. This contract is not a general GP0 stream parser.

Fill commands copy the candidate's VRAM into local pixel storage, apply
our existing fill semantics, then restore through `GPU::loadVram`.
At the pinned revision, that method copies pixel bytes without resetting
the command parser. No upstream source was changed. No write through a
const pointer was used. Other accepted commands go through `writeGP0`.
A payload word with high byte `0x02` remains upload data, not a fill.

The fill uses the same masks, rounding, wrap, and color reduction as
`components/platform/fill_vram.cpp`. Filled pixels clear bit 15; pixels
outside the fill retain all 16 bits. This differs from routing every
pixel through the existing `write_pixel`, which strips bit 15.

## Evidence

The final assertions cover the retained triangle, quad, and 4-bit palette
blended-quad pixels; fill alignment and rounded width; masked coordinates
and dimensions with wrap across both VRAM edges; RGB555 reduction; filled
and untouched mask bits; zero effective width and height; upload payload
handling; rejected empty, incomplete, extra, oversized, and unsupported
commands; and successful parser use after rejection.

The first run failed one combined assertion because the test coordinate
2031 masks to 992, rather than the intended 1008. Correcting the input to
2047 produced the intended masked position. The retained first log records
that failure. No renderer behavior was changed to resolve it.

This adapter copies the full 1 MiB VRAM out and back for each fill,
including no-op fills. Performance was not measured. The trial does not
establish production suitability, ordering-table traversal, display pages,
visible output, or retail agreement. The observed list used textured opcode
`0x2e`; this trial's raw `0x2f` sample does not establish modulation behavior
or complete menu command coverage.

## Provenance and next outcome

The unmodified dependency selection, revisions, archive hashes, and license
scopes are those in the [isolated GPU trial](ps1recomp-gpu-trial.md):
PS1Recomp under GPL-3.0-or-later and pinned fmt headers under MIT. No upstream
files were imported into public source. The tested host is macOS arm64 with
Apple clang 21.0.0. Other hosts remain untested.

Original adapter, commands, hashes, build logs, first and final run logs,
and dependency details remain under `build/coordination/gpu-fill-adapter/`.
The existing SDL2 source and window interface were unchanged. The repository
guard passed.

The fill boundary now has narrow synthetic evidence. The next outcome is
a bounded fixed 32-bit ordering-table adapter with empty tags and explicit
command boundaries. It must reject invalid links and unsupported payloads
without confusing packet boundaries with GP0 command boundaries. Test the
observed modulated textured-quad opcode separately before claiming menu
command coverage. A visible synthetic trial still precedes adoption.

The later [ordering-table trial](gpu-list-adapter-trial.md) passed 42
assertions, including split commands and one modulated `0x2e` sample.
It remains local and has no visible or adoption claim.
