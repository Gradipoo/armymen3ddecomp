# Visible synthetic GPU trial

## Outcome and acceptance

On November 17, 2026, display original synthetic geometry through the
[local ordering-table adapter](gpu-list-adapter-trial.md) and the existing
SDL2 presentation code. Require a real window observation, matching sampled
RGB readback, and preservation of candidate VRAM texture mask bits.

The principal observed the window titled `AM3D Synthetic GPU`. It displayed
a dark gray field, red upper-left triangle, green upper-middle quad, red
block with a brown blended interior, and dark red lower bar. Ten sampled
checks passed in both the dummy-driver run and the visible host run.
The visible runner completed its bounded run and exited zero.

The visible image also showed a dotted diagonal inside the brown blended
region. The later local probe below locates it in candidate VRAM. The visible trial does
not establish a clean textured quad or justify backend adoption.

## Presentation boundary

The runner uses the preceding adapter without changes. Original synthetic
list data produces the polygons, texture upload, palette upload, and one
modulated semi-transparent `0x2e` quad through the candidate GPU parser.
It copies candidate VRAM into a temporary `FillVram` solely for RGB display
through `SdlPlatform`. That copy strips bit 15 for display. It does not
replace the candidate's texture storage. The runner checks that candidate
VRAM remains unchanged and palette value `0x83e0` retains its mask bit.

The readback was 960 by 720. Sampled triangle, quad, blend, and background
colors were respectively `0xffff0000`, `0xff00ff00`, `0xff7b3900`, and
`0xff212121`. Each matched its expected value. These four samples do not
cover the visible diagonal artifact. The saved bitmap is renderer readback;
it is separate from the principal's live window observation.

The first restricted launch aborted with exit 134 after the VRAM checks.
The permitted host launch opened the real window, passed its readback
checks, and exited zero. The initial launch is retained as a failed attempt,
not a renderer acceptance result.

## Diagonal probe

A separate original local probe found `0x0167` at candidate VRAM coordinates
`(180,140)`, `(160,148)`, `(150,152)`, and `(130,160)`. Neighboring pixels
such as `(179,140)` and `(181,140)` were `0x00ef`. The value `0x0167`
is the second mode-zero blend of the modulated green foreground over the
first blended value: red 7 and green 11. This is consistent with a shared
quad edge being blended twice. It precedes the SDL display copy.

At the pinned candidate revision, `gpu.cpp` lines 950 to 953 split the quad
into triangles `(0,1,2)` and `(1,2,3)`. Lines 1222 to 1226 include zero-valued
edges for both, and lines 1277 to 1279 blend against current VRAM. This source
lead explains the sampled overlap. It is not a retail correctness finding.
The probe left the original runner source and binary unchanged. Its source,
log, command, and hash remain alongside the runner evidence.

## Evidence and limits

Sources, dependency notices, exact commands, hashes, dummy and host logs,
and synthetic frame remain under `build/coordination/gpu-visible/`.
`visible.log` records the failed launch; `visible-host.log` records the
successful host run. The local application bundle supplies only a test
identity and runner. No global installation or public source import occurred.

Dependency pins and license scopes are unchanged from the
[isolated GPU trial](ps1recomp-gpu-trial.md). The host was macOS arm64 with
Apple clang 21.0.0 and the installed SDL2 provider. Other hosts are untested.
The default disc-free source and SDL2 interface were unchanged. The
repository guard passed.

This trial uses no retail data or reconstructed game update loop. It does
not establish retail agreement, controller transitions, display-page
changes, complete menu command coverage, performance, or backend adoption.
The next bounded trial is a local shared-edge coverage fix with regression
checks for this synthetic quad and adjacent polygons. Keep the unmodified
dependency and failure evidence. A fix still needs visible confirmation
before adoption is considered.

The later [shared-edge fix trial](gpu-edge-fix-trial.md) passed six full
rectangle cases, and the principal observed the corrected uniform quad.
This remains a local synthetic result.
