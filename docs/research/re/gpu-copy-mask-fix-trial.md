# Copy mask-state fix trial

## Outcome and acceptance

On November 17, 2026, test a local copy-only mask-state fix for the two
failures in the [VRAM copy trial](gpu-copy-trial.md). Require those probes
to pass, normal nonoverlapping copies to preserve source bits, all four
mask modes to behave as specified, and existing adapter and edge checks
to remain passing.

The local variant passed both prior probes and six copy-mode regression
cases. The 42-check adapter suite and six full-rectangle edge cases passed.
This accepts a narrow local fix. Copy is still outside the adapter, and no
backend is adopted.

## Change and evidence

The local variant adds two copy-only flags, initializes them on reset,
updates them on GP0 `0xe6`, and consults them during GP0 `0x80` copy writes.
A protected destination is left unchanged. Otherwise the source value is
written with bit 15 forced when requested. The prior shared-edge change is
retained. Original source and failed logs remain untouched.

The [primary GPU reference](https://psx-spx.consoledev.net/graphicsprocessingunitgpu/#gpu-rendering-attributes)
assigns E6 bit 0 to forced bit 15 and bit 1 to destination protection.
Protection prevents overwriting an already marked destination even when
forcing is enabled. The code implements that behavior by checking protection
before writing; this does not claim a hardware-internal execution order.
The corresponding GPUSTAT bits are 11 and 12 in the
[status register reference](https://psx-spx.consoledev.net/graphicsprocessingunitgpu/#gpu-status-register).

The actual candidate command parser now preserves `0x8123` under protection
and produces `0x8000` under forcing, where the unchanged candidate had
produced `0x001f` and `0x0000`. Both original probes pass against the variant.

The six regression cases cover initial mode zero preserving all 16 source
bits, force mode, protection mode, combined protection and forcing,
transition from combined mode to zero, and clearing both flags by GP1 reset.
They use original synthetic nonoverlapping copies. All cases passed.

## Scope and provenance

This is explicitly copy-only behavior. GPUSTAT mask-bit readback, rendering
mask behavior, and CPU-to-VRAM mask behavior remain unmodeled. The public
reference describes wider mask effects than this local fix implements.
The existing fill behavior remains separate. The adapter was not extended
to expose `0xe6` or `0x80`, so it does not advertise general mask support.

Dimension masking, zero dimensions, overlap, wrap, performance, and retail
agreement are not established by these cases. No visible claim is needed
for these pixel-state checks. The observed menu copy's mask state remains
unknown.

Selected copied source remains PS1Recomp revision
`49c4a5164149a0b0eeaf1299f7cffa56d5ee1df1` under GPL-3.0-or-later, with the
preceding local edge patch and this mask patch. Pinned fmt remains under
MIT. License notices, exact commands, hashes, patches, and logs remain in
`build/coordination/gpu-copy-mask-fix/`. The dependency record is linked from
the [isolated GPU trial](ps1recomp-gpu-trial.md). No public runtime source
import, new download, retail data, or global installation occurred.

Tested host: macOS arm64, Apple clang 21.0.0. Other hosts remain untested.
The default source and SDL2 interface were unchanged. Default CMake
configuration and build passed. The repository guard passed.

The next bounded outcome is reference-backed overlap and wrap testing of
VRAM copies. Do not assume snapshot or ordinary memory-copy semantics.
Keep mask-state and dimension limits explicit before adapter extension.

The later [overlap and wrap trial](gpu-copy-overlap-trial.md) passed
2060 pixel assertions before a width-mask failure. Overlap results remain
exploratory and copy remains outside the adapter.
