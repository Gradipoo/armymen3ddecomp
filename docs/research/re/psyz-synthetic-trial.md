# PsyZ synthetic renderer trial

## Outcome and acceptance

On November 17, 2026, trial the graphics candidate with original synthetic
inputs for services seen in the first-screen observation. Accept adoption
only after the needed interfaces, pixel behavior, dependency licenses, and
visible output pass. A source review or renderer-only pass is insufficient.

The local renderer check passed eight pixel assertions. A separate fill
alignment check failed. Adoption is not accepted. No game function status
changes. See [first-screen-observation.md](first-screen-observation.md).

## Source and scope

The candidate is [PsyZ revision
3413eeb8cd16bfcc3c5a7041bd1392b31bc1c5cc](https://github.com/Xeeynamo/psyz/tree/3413eeb8cd16bfcc3c5a7041bd1392b31bc1c5cc).
The downloaded archive SHA-256 is
`db5c1cd34f413487cd828680562d12e064270aa22b83a29822ec3df5287c2b2a`.
The archive URL pins the revision; no Git checkout identity was verified.

The selected software renderer and internal implementation headers fall
under the root license's MPL-2.0 scope. Its direct and transitive headers
under `psyz/include` are marked unlicensed by that license. The separate
MIT decompilation subtree was not selected. This trial establishes no grant
for the unlicensed headers. No third-party code was imported into our source.
No proprietary SDK or root make target was used.

The host was macOS arm64 with Apple clang 21.0.0 and installed SDL3 3.4.20.
The narrow runner does not link SDL. The upstream archive lacks its SDL
submodule. Full backend build, display, input, and other hosts remain untested.

## Executed checks

The local build exited zero. The positive runner exited zero with eight
checked pixels: aligned clear, flat quad, flat triangle, image upload,
nonoverlapping image copy, a 4-bit palette textured quad with
semi-transparency, clipping, and a synthetic fixed 32-bit list with an empty
tag. The list adapter copies words into host types before calling the
software renderer. It does not reinterpret retail links as host pointers.

These are narrow samples. The runner calls `software_rasterizer` directly.
It does not execute `DrawOTag`, SDK `LoadImage`, raw GP0 transfer dispatch,
display page switching, controller input, or a retail packet replay. It does
not establish whole-list correctness or agreement with retail output.

The separate fill test exited one. For rectangle `(3, 0, 1, 1)`, our existing
GPU fill reference requires red at `(0, 0)` and `(15, 0)` after horizontal
alignment and width rounding. Both renderer pixels were zero. Source review
shows the GP0 fill handler passes the raw rectangle to this clear routine;
that dispatch path was not executed. The backend was not patched to hide
the mismatch. No visible trial was needed to reject this candidate as-is.

The existing SDL2 smoke target rebuilt. The focused `fill_vram`, `front_tim`,
and `sdl_platform` tests passed, three of three. These host checks preserve
the existing baseline; they do not prove a newly observed visible result.

## Evidence and next outcome

Original runner, selected dependency list, commands, exits, hashes, and logs
stay under `build/coordination/psyz-trial/`. Baseline build logs stay under
`build/coordination/graphics-tools/`. No retail data was needed for this trial.

The tested renderer subset is useful evidence, not an adopted backend.
Do not repeat this trial unchanged. A retry needs a specific fill fix and a
credible license path for the selected dependencies. The next bounded
outcome is to choose a reusable component with explicit license coverage
for the observed flat polygons and textured quads, while preserving the
existing SDL2 window. Do not combine that choice with a backend migration.

The later [isolated PS1Recomp GPU trial](ps1recomp-gpu-trial.md) found a
licensed primitive path with three passing samples and the same fill
alignment limit. It remains unadopted.
