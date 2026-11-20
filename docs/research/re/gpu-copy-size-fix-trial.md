# Copy dimension-mask fix trial

## Outcome and acceptance

On November 19, 2026, test a minimal local fix for the dimension-mask failure
in the [overlap and wrap trial](gpu-copy-overlap-trial.md). Require width
and height masking, zero-to-maximum behavior, unchanged pixels outside the
normalized rectangle, and preservation of earlier passing checks.

The local variant passed 15360 boundary and guard pixel checks. The same
regression found 1536 failing pixels in the prior variant. All 2061 prior
reference-backed copy assertions now pass. The copy-mask cases, prior mask
probes, 42-check adapter suite, and six shared-edge cases also pass.
Copy remains outside the adapter. No backend is adopted.

## Change and evidence

Only copy dimension normalization changed relative to the local copy-mask
variant. Width is `((raw_width - 1) & 0x3ff) + 1`; height is
`((raw_height - 1) & 0x1ff) + 1`. Unsigned arithmetic retains zero as maximum
size. Coordinate wrapping, mask handling, and the existing in-place loop
were not changed.

The expected dimensions follow the
[GPU memory transfer reference](https://psx-spx.consoledev.net/graphicsprocessingunitgpu/#gpu-memory-transfer-commands).
The boundary regression uses explicit expected lengths for five raw widths:
0, 1024, 1025, 2048, and 65535. Their expected lengths are respectively
1024, 1024, 1, 1024, and 1023. Five raw heights are 0, 512, 513, 1024, and
65535, with expected lengths 512, 512, 1, 512, and 511.

Width cases use distinct source and destination rows. Height cases use
distinct source and destination columns, so even full-height copies remain
nonoverlapping. Each case checks the complete destination row or column,
including pixels outside the expected length, and an adjacent guard row
or column. The fixed variant had no failures. This independently covers
zero and maximum height, which the preceding trial had left open.

The earlier width-1025 probe now preserves the second destination pixel.
All earlier reference-backed nonoverlap, wrap, coordinate, and width checks
pass. The four overlap outputs remain exploratory observations only. This
fix does not supply a hardware overlap oracle or alter copying order.

## Provenance and limits

The selected copies derive from PS1Recomp revision
`49c4a5164149a0b0eeaf1299f7cffa56d5ee1df1`, GPL-3.0-or-later, with the prior
local edge and copy-only mask changes plus this dimension patch. Pinned fmt
remains unchanged under MIT. Original dependencies, variants, notices, and
failed evidence remain untouched. No public runtime source was imported.

Source, patch, exact commands, hashes, setup-error logs, before/after runs,
and regression logs remain under `build/coordination/gpu-copy-size-fix/`.
The host was macOS arm64 with Apple clang 21.0.0. Other hosts, performance,
and retail agreement remain untested. No retail data, UI, download, global
installation, or default source change was needed. The repository guard
passed.

The local copy implementation now has bounded reference-backed size, wrap,
and mask evidence. Overlap remains unverified, and mask support remains
copy-only rather than general E6 behavior. A later adapter extension must
reject source/destination overlap or obtain a credible overlap oracle. It
must also define its mask-state contract without advertising unsupported
rendering, upload, or GPUSTAT behavior.

The later [restricted copy adapter trial](gpu-restricted-copy-trial.md)
supports nonoverlapping copies under a fixed zero-mask-state contract.
Overlap and E6 commands reject before execution. It remains local.
