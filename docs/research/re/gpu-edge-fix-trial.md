# Textured shared-edge fix trial

## Outcome and acceptance

On November 17, 2026, test a local fix for the double-blended diagonal found
in the [visible synthetic trial](gpu-visible-trial.md). Require shared-edge
ownership without gaps or duplicate blending in the selected synthetic
rectangles, preserve existing samples, and inspect the corrected window.

The local variant passed all six full-rectangle cases. The unmodified
candidate failed those same cases. The principal observed the corrected
window with a uniform brown blended quad and no former dotted diagonal.
This accepts the bounded synthetic fix, not retail accuracy or adoption.

## Change and evidence

The candidate normalizes triangle winding before evaluating edge weights.
The local change includes a zero-weight edge only when its directed edge
has positive vertical delta, or zero vertical delta and negative horizontal
delta. Reversing an edge reverses its ownership. With downward-increasing
coordinates and integer samples, the tested rectangle includes its top and
left edges and excludes its bottom and right edges.

Only the coverage condition in the ordinary textured-triangle rasterizer
changed. The original dependency remains untouched. Flat and Gouraud
rasterizer paths were not changed or verified by this fix.

The regression checks every one of 4000 interior pixels plus a one-pixel
border for six cases: two quad orientations, and separately submitted
triangles with both windings along both rectangle diagonals. Expected
interior color is the once-blended `0x00ef`; `0x0167` exposes a second blend.
The original failed all six cases, each with 19 or 20 interior double blends
and 141 excluded-border differences under the declared synthetic contract.
The local variant had no missing, duplicate-blended, or other mismatched
pixels. These results do not define the PS1 hardware rasterization rule.

The SDL runner also passed its ten existing VRAM and readback samples under
the dummy driver. The principal then launched the local `AM3D Edge Trial`
window on the real host and inspected its screenshot. The blended quad was
uniform. The visible run passed all ten samples and exited zero. The prior
42-check list-adapter suite also passed against the variant. These results
are retained locally.

## Provenance and limits

The local variant contains selected copies from PS1Recomp revision
`49c4a5164149a0b0eeaf1299f7cffa56d5ee1df1` under GPL-3.0-or-later. Its
license and notices remain with the copied files. Pinned fmt
`f99d53024782bf928b07839140862163f15ade5b` remains unchanged under MIT.
Full dependency records are in the [isolated GPU trial](ps1recomp-gpu-trial.md).
No upstream source was imported into public runtime code.

Sources, original and modified binaries, exact commands, hashes, license
notices, regression logs, frame, and host log remain under
`build/coordination/gpu-edge-fix/`. The host is macOS arm64 with Apple clang
21.0.0 and installed SDL2. Other hosts remain untested. No retail data was
used. The default build and SDL2 interface were unchanged. The repository
guard passed.

Arbitrary triangles, clipping, Gouraud texturing, other texture formats,
performance, and retail agreement remain untested. The candidate is still
not adopted. The next bounded service from the observed list is VRAM copy
`0x80`, with synthetic overlap and boundary checks. The unresolved `0x00`
start and full menu command coverage remain separate observations.

The later [VRAM copy trial](gpu-copy-trial.md) found two failed mask
assertions through the real command parser and stopped before adapter
extension. The observed menu copy's mask state remains unknown.
