# Local live GPU-status accessor

## Outcome and acceptance

On November 19, 2026, add a local observer that reads the emulator's GPU
status handler instead of debugger shadow memory. Require the registered
Lua interface to report software-renderer mask settings 0 through 3 and
clear both bits after GP1 reset, using synthetic commands without a disc.

The filtered no-disc test passed. The local test executable and app
executable built successfully. No app window, retail capture, or game
function verification is claimed.

## Observer and executed test

The local patch registers `PCSX.GPU.readStatus()` through the existing Lua
FFI binding. Its C++ wrapper calls `GPU::readStatus()`. It does not use
`getMemoryAsFile`, whose hardware reads were rejected in the
[method review](gpu-mask-capture-method.md).

It also avoids `readStatusFromBus`, which additionally consults beam counters
and can advance them according to source comments. This accessor reports
emulator status, not an independently verified hardware value. Its full
word is not identical to the guest bus-derived status in every bit.

The original local test uses the upstream software-GPU fixture, initializes
fixture memory, registers the Lua binding, sends GP0 E6 settings 0, 1, 2,
and 3 through `GPU::writeData`, and reads each through the Lua accessor.
All four comparisons of bits 11 and 12 passed. GP1 reset through
`GPU::writeStatus` then cleared both bits. The filtered test exited zero.
No game instructions, disc, or BIOS were needed for this test.

The first runtime attempt crashed during reset because this GPU-only fixture
had not initialized memory used by IRQ reset. Initializing and shutting down
fixture memory fixed that test setup. The original crash output is retained.
An unmodified upstream flat-quad fixture also passed. This does not establish
all possible accessor side effects or test other backend behavior.

## Backend and build limits

At this source revision the OpenGL backend returns a status constant with
both mask bits clear; it cannot meet this mask-state acceptance. The
software backend updates them from E6. Run 11's saved settings select the
software renderer, but a fresh observation must establish the effective
backend rather than assume configuration proves it.

The build uses PCSX-Redux revision
`7637751dc246876ee658e94825d9c91129fef820` with this observer and a separate
synthetic test patch. That pin matches prior bundle metadata, not independent
proof of the prior binary's provenance. Source notices declare
GPL-2.0-or-later; third-party submodules retain separate notices and recorded
revisions. No source was imported into the public runtime.

All source, patches, licenses, dependency versions, submodule revisions,
commands, hashes, and logs remain under
`build/coordination/live-gpu-accessor/`. Test binary SHA-256:
`aa52ac8b6e9c8e156d189dacf720a24e6707422eb01f8b94ea898f016d488dd9`.
App executable SHA-256:
`c40d8f2160176fa0880199427379ccbb64ba1605f58db2c8372cfb4f885ff17e`.

An attempted command-line optimization override suppressed dependency-specific
include flags and caused a missing-header build failure. Affected objects
were rebuilt using the Release optimization variable instead. The final
local correctness build mixes completed optimized objects with later
unoptimized objects; no performance claim follows.

The app executable has absolute Homebrew library dependencies and has not
been launched. Standard bundle packaging requires absent `dylibbundler` and
would install it; that step was not run. No global dependency was installed.
The original emulator remains unchanged. Tested host: macOS arm64 with Apple
clang. Other hosts remain untested. The repository guard passed.

## Next observation

Prepare an isolated local launch using this binary and its matching resources,
then capture mask state at the selected submission with backend identity,
frame, caller, finite budget, and verified cleanup. An entry sample alone
still cannot establish state at the later copy without ruling out intervening
E6 commands or resets. The retained zero commands remain a separate issue.

The later [menu entry observation](menu-mask-entry-observation.md)
validated an isolated visible launch and sampled both mask bits as zero
at a new menu submission. State at copy processing remains unobserved.
