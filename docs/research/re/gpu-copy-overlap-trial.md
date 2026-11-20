# VRAM copy overlap and wrap trial

## Outcome and acceptance

On November 19, 2026, test the unchanged local copy-mask variant through its
actual GP0 command path. Require reference-backed results for nonoverlap,
coordinate masks, wrapping, and bounded dimension cases. Record overlap as
observations where the reference does not establish an ordering rule.
Stop at the first confirmed mismatch. Keep copy outside the adapter.

The build passed. The runner passed 2060 pixel assertions, then failed one
width-mask assertion and exited one. Four overlap cases were exploratory,
not hardware pass results. No source fix or adapter extension was made.

## Reference and executed checks

The [GPU memory transfer reference](https://psx-spx.consoledev.net/graphicsprocessingunitgpu/#gpu-memory-transfer-commands)
defines source and destination coordinate masks, independent wrapping at
VRAM edges, and dimension conversion `((size - 1) & mask) + 1`. Zero maps
to maximum width or height. The reviewed section does not establish an
ordering or buffering rule for overlapping copies.

Original synthetic pixels passed checks for ordinary nonoverlapping copy,
source X and Y wrap, destination X and Y wrap, and masked source and
destination coordinates. All 1024 destination pixels were checked for
both zero width and explicit width 1024. These checks do not establish zero
or maximum height behavior; the run stopped before later cases.

The final probe requested width 1025 and height 1. The reference converts
that width to 1. The first destination pixel at `(20,20)` correctly became
`0x1111`. The next at `(21,20)` should have remained `0x4444`, but became
`0x2222`. This confirms the source-review finding that nonzero dimensions
are used without the required masks. The probe stopped at that failure.

## Exploratory overlap observations

Four cases copied five pixels within six initialized pixels, horizontally
and vertically in both directions. Initial values were `0x0100` through
`0x0105`. The rightward and downward copies propagated `0x0100` across all
six pixels. The leftward and upward copies produced `0x0101` through
`0x0105`, followed by another `0x0105`.

Those outputs match the candidate's forward in-place loop. The harness also
records a conditional snapshot model, which differs for rightward and
downward copies. Neither model is a hardware oracle. No retail agreement
or correct overlap behavior is claimed.

## Provenance and next outcome

The selected source is the unchanged local variant from the
[copy mask-state trial](gpu-copy-mask-fix-trial.md), based on PS1Recomp
`49c4a5164149a0b0eeaf1299f7cffa56d5ee1df1` under GPL-3.0-or-later with local
edge and copy-mask patches. Pinned fmt remains unchanged under MIT.
Dependency notices and fingerprints remain in the linked trial records.
Original source, exact commands, hashes, build/run logs, and observations
stay under `build/coordination/gpu-copy-overlap/`.

The host was macOS arm64 with Apple clang 21.0.0. Other hosts remain
untested. No retail data, new dependency, public runtime import, or visible
test was used. The existing adapter and GPU sources were unchanged, so their
prior regression suites were not redundantly rerun. The repository guard
passed.

The next bounded fix is copy dimension masking, retaining zero-to-maximum
behavior, followed by width and height regression cases. Overlap remains
unverified. Any later adapter contract must keep that limit explicit rather
than treating these exploratory observations as hardware acceptance.

The later [dimension-mask fix trial](gpu-copy-size-fix-trial.md) passed
15360 boundary and guard checks and all prior reference-backed assertions.
Overlap remains unverified and copy remains outside the adapter.
