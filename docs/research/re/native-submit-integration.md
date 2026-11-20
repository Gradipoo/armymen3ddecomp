# Native reconstructed submission integration

## Outcome

On November 20, 2026, connect the implemented
[submission function](call-8007c11c.md) to the existing restricted GPU
adapter. Two original test ordering tables rendered successfully through
that function. The principal observed the resulting owner-file soldier
texture in the native window. Backend adoption and menu update remain open.

## Boundary and checks

The bridge implements the function's named service interface and maps a
checked, aligned 32-bit guest address into a bounded 16 KiB synthetic RAM
region. It does not cast guest values to host pointers. Three reverse-linked
table tags lead through empty tags to an original command node containing
fill and `0x2f` quad commands. The existing list adapter is unchanged.

The function computes final tags `0x80010108` and `0x80010508` for the two
test tables. Each frame checks DrawSync, branch-word read, and DrawOTag
order. The branch word is fixed zero, matching the observed path. The
nonzero callback path is not implemented by this local backend bridge.

`upload_front_tim` supplies the texture through the adapter's actual image
transfer path. Both frames independently compare all 76800 display RGB
values with a CPU reference, including cleared pixels outside the quad.
All 1424 uploaded words match. Original synthetic data tests transparent
and bit-15 semi-transparent colors, including 704 blended quad pixels per
frame. Owner, synthetic, and missing-file fallback runs pass.

A late unsupported E6 command, overlapping copy, cyclic list, and invalid
starting address reject without changing VRAM. The final SDL frame passes
76800 source-pixel-center readback comparisons. These are original host
inputs, not captured retail packet replay or renderer equivalence evidence.

The two frames are generated before presentation. The window then presents
the final diagnostic frame; it does not run reconstructed game updates.
Positions `(234,56)` and `(120,56)` are stand-ins, not measured menu layout.

## Visible result and provenance

The first window-control attempt expired. Its bounded app run exited zero
and its checks are retained. After resetting the control session, a fresh
run displayed the green soldier at the second diagnostic position. The
principal inspected the live screenshot and the process exited zero.

The frozen executable SHA-256 is
`1851a39437d0d3216ec7cca765afad50b92116fbb51ed1c3b5f41f96fd235970`.
Source, commands, dependency records, license notices, hashes, and logs stay
under `build/coordination/native-submit-integration/`. The unchanged local
GPU candidate and dependency pins remain those in the preceding trials.
No public runtime dependency, CMake change, retail capture, or global install
was introduced. The host is macOS arm64 with installed SDL2; other hosts
and performance are untested. The repository guard passed.

The next game-facing outcome is to identify the controller-status caller's
button and selection path. The observed return `0x80064e58` is a lead only.
This integration does not establish the native menu or promote function
status beyond the implemented submission wrapper.
