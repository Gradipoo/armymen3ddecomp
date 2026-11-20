# Menu GPU mask entry observation

## Outcome and acceptance

On November 19, 2026, validate the isolated local observer build and sample
GPU mask bits at the selected menu submission. Require a real window,
visually correlated retained frames, a gated live-accessor record, bounded
list counts, and capture cleanup without error.

The local build reached the retail menu. At frame 3935 both mask bits were
zero at DrawOTag entry. This establishes entry state in this new run only.
It does not establish state at the later copy or in the historical run 11.

## Run identity and steps

The executable SHA-256 is
`c40d8f2160176fa0880199427379ccbb64ba1605f58db2c8372cfb4f885ff17e`,
the locally built [live-status observer](live-gpu-status-accessor.md).
Its source is pinned PCSX-Redux with the local observer patch. Matching
checkout resources are linked in an isolated local app wrapper. Absolute
Homebrew libraries remain host dependencies. The original emulator and
prior capture bundles were unchanged.

The run used the owner's USA cue, local BIOS `scph5501.bin`, interpreter,
no fast boot, fresh copies of the preserved initial cards, isolated
settings, and explicit non-threaded software-GPU switches. BIOS detection
reported SCPH-7003 (US), identity `8d8cb7e4`. Each initial card hash was
`78b6d4ac9ab4d23caf7e5f04f83539bf5d994cccfb0a709d14ac53d05c8e21ef`.
Card contents and effective controller type were not independently decoded.
Web and GDB servers were disabled.

The principal observed the Army Men 3D title window, pressed Return for
200 ms, then observed `1 PLAYER` with `NEW GAME` selected. This is a host
input duration, not a measured guest input edge. The principal created the
capture gate only after that menu observation. Saved frames 3900 and 3960
were subsequently inspected and both show the same selected menu.

Software selection follows the explicit launch switches and the known
source selection path. There is no independent runtime backend identity
API result. The successful window and capture validate this local launch;
they do not establish renderer agreement with hardware.

## Captured result and cleanup

The hook at `0x80086bbc` accepted caller return `0x8007c168`. At frame 3935,
`a0` was `0x800ccd14`. The new live accessor returned `0xd404260a` with
bit 11 equal to zero and bit 12 equal to zero. It sampled before walking
list tags. The bounded tag walk reached the terminator with 2758 nodes
and 2256 payload words. No packet payload or VRAM data was saved by this
status hook.

The armed and capture-stop messages are present. No capture or cleanup
error was logged, and stderr was empty. The listener-removal path ran and
the breakpoint callback returned false; no separate removal probe was made.
The principal then interrupted the emulator process, exit 255. This is not
a clean full-budget process exit.

## Limits and next observation

The historical exit-transition capture had 2798 nodes and 2455 words.
This new menu submission has different counts. Do not transfer its entry
state to the [older retained list](menu-list-contract.md), assume the lists
are identical, or treat the identical-source copy as an established no-op.
An entry sample cannot exclude E6 or reset activity before the copy.
The zero-command effect also remains unresolved.

Exact arguments, environment, scripts, hashes, cards, neighboring frames,
status record, and logs remain under `build/coordination/status-capture/`.
The repository guard passed. No public runtime source was imported, and
no game function status changes.

The next bounded observation is mask state at copy processing, or equivalent
evidence excluding intervening state changes for that same submission.
Keep the new stable-menu sample distinct from the old exit-transition list.
