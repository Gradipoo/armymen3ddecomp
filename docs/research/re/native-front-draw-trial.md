# Native FRONT.TIM drawing trial

## Outcome and acceptance

On November 20, 2026, connect the public `upload_front_tim` service to native
textured drawing and SDL2 presentation. Require synthetic and missing-file
fallbacks, independently checked texture colors and transparency, preserved
candidate VRAM, and a real owner-file window observation.

The principal observed the FRONT.TIM soldier texture in the native window.
Synthetic, missing-input, and owner-file automated runs passed. This accepts
the local asset drawing path, not a reconstructed menu or backend adoption.

## Native path

The local runner reads the owner file when present or constructs original
synthetic bytes with the same measured layout. The public uploader submits
the palette and packed words through actual GP0 image transfers into the
existing local GPU candidate. A raw opaque 4-bit textured quad, opcode
`0x2d`, samples texture page `(640,0)` and palette `(512,506)`.

The quad is 44 by 128 at diagnostic position `(234,56)`. It is not a retail
placement or identified retail primitive. The retained menu's two `0x2e`
layout leads instead use palette `(512,500)` and texture page `(576,0)`.
Do not treat those primitives as FRONT.TIM draws.

A separate RGB-only copy feeds the existing `SdlPlatform`. Candidate texture
storage remains 16-bit and unchanged by that presentation copy. The original
platform smoke source and its default behavior were not changed.

## Executed checks

All 1424 uploaded words matched the input in each automated path. The
independent CPU reference decoded the file indices and palette to compare
all 5632 quad RGB values, including transparent pixels against the background.
Synthetic and fallback inputs had 352 transparent pixels; the owner file had
1694. Palette values, including a synthetic bit-15 entry, were preserved.

Each run checked 76800 source-pixel-center RGB samples in the 960 by 720 SDL
readback and compared all candidate VRAM words before and after presentation.
No RGB mismatch or presentation-induced VRAM change was found. These are
native transport and drawing checks, not a retail renderer comparison.

The principal's final owner-file run used executable SHA-256
`112f3dd7b7ee3176698049d19671cb9ba220a51e125074d0e9f496fea4cf5ec9`.
The live window showed the green soldier against the dark background, and
the process exited zero. An earlier app-ID selection timed out; selecting
the registered app name on a new run succeeded. The binary was frozen before
that final observed run. Earlier handoff and launch logs remain local.

## Provenance and next integration

The runner and original fixture remain under
`build/coordination/native-front-draw/`, alongside commands, hashes, logs,
local frame, and manifest. Owner data and rendered captures stay local.
The public uploader is original project code. The unchanged local GPU
candidate remains pinned PS1Recomp plus the recorded edge, copy-mask, and
copy-size patches under GPL-3.0-or-later; pinned fmt remains MIT. Selected
source, license, and dependency details are retained in preceding trials.
No new dependency, download, public runtime import, or CMake change occurred.

Tested host: macOS arm64 with Apple clang and installed SDL2. Other hosts
and performance remain untested. The repository guard passed.

The file-to-native-texture path now works in a visible local trial. The next
screen work must connect measured game drawing and update behavior rather
than enlarge this diagnostic. FRONT.TIM's retail draw site remains unknown;
the identified menu primitives and their input-driven changes are separate
integration work. No game function status changes.
