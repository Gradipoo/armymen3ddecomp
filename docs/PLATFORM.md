# Host platform foundation

The optional SDL2 host implementation displays the known fill packet,
polls a controller, and paces synthetic frames. It is a platform test,
not a running Army Men scene. The roadmap's full platform milestone is
still open. No game files or assets are needed for this test.

## Build and run

The default build remains free of third-party runtime libraries. To build
the host test, supply SDL2 development files for your machine and enable:

```
cmake -S . -B build/host-sdl -DAM3D_WITH_SDL2=ON -DCMAKE_BUILD_TYPE=Release
cmake --build build/host-sdl --config Release
ctest --test-dir build/host-sdl -C Release --output-on-failure
```

SDL2's CMake package may need a local `CMAKE_PREFIX_PATH`. SDL2 2.0.14 or
later is required for the virtual controller test. No dependency is fetched
at configure time. Our code is GPL-3.0-or-later. SDL and sdl2-compat use the
zlib license. Their notice is kept in `third-party/SDL-LICENSE.txt`.

On a single-configuration host build:

```
./build/host-sdl/am3d_platform_smoke --frames 120 --capture
```

On Windows with a multi-configuration generator, use the executable in
the selected configuration folder. The test opens a window and exits
after the requested number of frames. When `build/disc/DATA/FRONT.TIM`
is present, the window draws that 44 by 128 picture. The file stays
under `build/`. The layout is recorded in
[front-tim.md](research/re/front-tim.md). When the file is absent, the
window presents synthetic color bars.
A controller's D-pad moves the marker, its cross/A button changes the
marker color, and Start ends the test. Closing the window also ends it.
There are no keyboard game bindings. Keyboard play remains a future lane.

`--capture` saves a local BMP under `build/platform/`. Captures from a
future game renderer may contain assets and must stay local. `--hidden`
is available for local automation. The CTest integration test uses SDL's
dummy video driver and a virtual controller. A dummy-driver pass alone
does not prove a visible window works.

## Supported behavior and evidence

Our fill sink accepts the known three-word GPU fill command after its
packet tag. It rejects unsupported commands. It applies 16-pixel horizontal
alignment, dimension masks, VRAM wrapping, and RGB555 conversion. The
hardware reference is [the PS1 GPU specification](https://psx-spx.consoledev.net/graphicsprocessingunitgpu/).
The presenter converts a selected VRAM view for a 4:3 host viewport.

The sink connects directly to our `fill_display` interface. Tests check
wrapping, rounding, zero dimensions, unsupported inputs, rendered pixels,
button press/release, controller removal, and quit events. The synthetic
controller test covers digital input and a trigger. It does not prove
compatibility with every physical controller.

The reconstructed display-buffer advance now applies the display and draw
environments through this host interface. Native indices represent the
buffer links. The SDL integration test fills two synthetic VRAM pages with
different colors, advances twice, and checks the selected page pixels and
next drawing origin. The visible smoke loop uses this same advancement
to alternate its drawing pages. Its 120-frame run and capture were checked
after this integration. The additional C++ state test covers list wrapping,
environment ordering, mode selection, and arithmetic truncation.

The presenter supports the non-interlaced, 15-bit mode used in the recorded
boot state. Interlaced and RGB24 presentation are rejected explicitly.
Mode 3 controls RGB24, not interlace; the corrected ABI interpretation is
recorded in [display-environment-layout.md](research/re/display-environment-layout.md).
Drawing-environment
fields are retained for future commands; polygon and texture rendering
remain unimplemented. This does not make the retail scene loop complete.

The reconstructed startup clear loop now advances and fills every counted
buffer before the smoke loop starts. It reads the live count after each
fill. Host checks include count changes and drawing-state changes during
the wait. State for the fill packet is acquired after `DrawSync`, rather
than copied by the caller before waiting. The SDL test confirms both
synthetic pages are black after the startup clear, then tests presentation
using independently colored pages.

On November 13, 2026, the local Mac build passed all three C++ tests. The
visible smoke test presented 120 frames. Its captured image was inspected.
The installed provider was sdl2-compat 2.32.74 on ARM64, not original SDL2.
That is a tested SDL2 API provider; native SDL2 on other systems still
needs its own results. The library is dynamically linked from the existing
host installation. No SDL source or binary is copied into this repo.

Host pacing uses a monotonic clock. It is not a PS1 cycle or VBlank model.
Disc loading still uses the existing launcher and extraction tools. The
host renderer has no CD streaming interface, geometry pipeline, texture
commands, audio, movies, or retail scene loop yet. No function's ledger
status was promoted to verified because this platform test passed.

## PsyCross evaluation

Source: [OpenDriver2/PsyCross](https://github.com/OpenDriver2/PsyCross) at
`e56e4cde1c2b8a15e0d4e38b26cdd9202e0d17e6`. Its archive SHA-256 is
`8e88759f848b32dc29ef345150ca5dbe9f4c56de3eef8cff29b3b58d68ff6dd1`.
The reviewed root license is MIT, copyright 2020 REDRIVER2 Project.
The trial source, local edits, and logs remain under `build/platform/`.
No upstream files have been imported into the public source tree.

| Attempt | Result |
| --- | --- |
| 1 | GPU packet assertions failed on ARM64. The native-pointer header size selected the 32-bit branch. |
| 2 | A pointer-width condition fixed that layout issue. Narrowing initializers and OpenAL header discovery still failed. |
| 3 | Explicit casts and the installed OpenAL-soft paths resolved those errors. Remaining errors included pointer-to-int conversion and signed lookup-table initializers. |

The trial stopped after three failures. Static assertions were retained.
The source's primitive parser was also reviewed. Its command-zero group
does not handle the fill opcode used by our reconstructed display function.
Simply forwarding the packet would not demonstrate a working fill.
Its README lists unfinished movie and CD/XA audio support as well.

SDL2 was selected for the host display and input boundary. The tested fill
sink is our code. This is a partial foundation toward the required PS1
interfaces, not a substitute for completing them. PsyCross remains a
research lead for separately evaluated components.

## Native FRONT.TIM upload service

`upload_front_tim` now submits the measured palette and packed pixel blocks
to a caller-provided sink after validating both blocks. It preserves all
16 bits and rejects wrapping rectangles. See the
[file and upload record](research/re/front-tim.md#native-upload-service).
The default and optional SDL2 builds retain their existing dependencies.
The smoke window still uses its decoded-image stand-in. A local GPU-parser
integration passed, but no backend or game loop is adopted by this API.

A later [native drawing trial](research/re/native-front-draw-trial.md)
passed whole-quad RGB checks for owner, synthetic, and missing-file inputs.
The principal observed the soldier texture in a native window. Placement
remains diagnostic, and the game update loop is not connected.

The [reconstructed submission integration](research/re/native-submit-integration.md)
routes two original test tables through the implemented game submission
wrapper into the local adapter and native window. It retains a fixed zero
branch word and diagnostic placement; menu selection and updates remain open.
