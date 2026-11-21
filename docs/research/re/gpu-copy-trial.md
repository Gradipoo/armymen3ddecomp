# VRAM copy mask trial

## Outcome and acceptance

On November 17, 2026, trial the observed four-word GP0 `0x80` copy service
before adding it to the local adapter. Require reference-backed expectations
for normal copies, overlap, boundaries, and mask bits. Stop at a confirmed
source and execution conflict instead of treating partial support as ready.

The build passed. The direct command-path runner exited one with two failed
mask assertions. Copy support was not added to the adapter. No GPU source
was changed and no backend was adopted.

## Reference and source review

The [psx-spx GPU transfer and mask-bit sections](https://psx-spx.consoledev.net/graphicsprocessingunitgpu/)
describe the four-word VRAM-to-VRAM copy command, masked dimensions with
zero meaning maximum size, coordinate wrap, and mask settings controlled
by GP0 `0xe6`. The mask settings can preserve protected destination pixels
or force bit 15 in written pixels. These are specification expectations,
not measured Army Men behavior.

The pinned candidate's `executeCopyVRAM` uses unmasked nonzero 16-bit sizes,
replaces zero dimensions with 1024 and 512, and copies forward in place
with coordinate wrap. Its source comment leaves hardware overlap behavior
uncertain. The copy does not consult mask state, and the candidate treats
GP0 `0xe6` as a no-op. No overlap correctness claim follows from that comment.

## Executed evidence

An original synthetic upload initialized four pixels at `(10,10)` through
`(13,10)` to `0x001f`, `0x8123`, `0x0000`, and `0x0456`.
The runner then sent commands through the actual candidate `writeGP0` path:

- Set mask protection with `0xe6000002`, then copy one pixel from `(10,10)`
  to `(11,10)`. Expected destination `0x8123`; actual `0x001f`.
- Set mask forcing with `0xe6000001`, then copy one pixel from `(12,10)`
  to `(13,10)`. Expected destination `0x8000`; actual `0x0000`.

Both assertions failed. This confirms the selected mask mismatch. It does
not establish all other copy semantics. The trial stopped before normal,
overlap, dimension-mask, and wrap regression suites or adapter extension.
The observed menu list's required mask state remains unknown, so this does
not prove that its particular copy fails.

## Provenance and next outcome

The trial links the existing local shared-edge variant from the
[edge-fix trial](gpu-edge-fix-trial.md). Its copy code is unchanged from
PS1Recomp `49c4a5164149a0b0eeaf1299f7cffa56d5ee1df1`, GPL-3.0-or-later.
Pinned fmt remains unchanged under MIT. Selected dependency notices and
hashes remain in the prior trial records. No download, public source import,
retail data, visible test, or global installation was needed.

Probe source, exact commands, source and binary hashes, and build/run logs
remain under `build/coordination/gpu-copy-trial/`. Tested host: macOS arm64,
Apple clang 21.0.0. Other hosts and performance remain untested. The default
build and SDL2 source were unchanged. The repository guard passed.

Do not repeat the unchanged trial. A later bounded fix needs explicit copy
mask-state handling and regression coverage before adding `0x80` to the
adapter. Normal, overlapping, and wrapping copies still need separate
expectations and checks. Do not infer those semantics from these two mask
samples or promote game function status.

The later [copy mask-state fix trial](gpu-copy-mask-fix-trial.md) passed
the two probes and six copy-mode cases. It remains copy-only and local;
the adapter and broader mask behavior remain unchanged.
