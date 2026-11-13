# Display environment layout at 0x80076164

This corrects a field label in [call-80076164-second.md](call-80076164-second.md).
That block note is retained unchanged. Its description of the mode-controlled
byte as interlace is wrong. The byte at state offset `0x3d` is offset `0x11`
within the display environment, and is the RGB24 flag. Mode 3 enables it.

The compatible [PsyCross header](https://github.com/OpenDriver2/PsyCross/blob/e56e4cde1c2b8a15e0d4e38b26cdd9202e0d17e6/include/psx/libgpu.h)
declares two rectangles followed by `isinter`, `isrgb24`, and reserved bytes.
The independent [PSn00bSDK header](https://github.com/Lameguy64/PSn00bSDK/blob/master/libpsn00b/include/psxgpu.h)
uses the same two flag offsets. No header code was copied into our runtime.

A local compile-time check against the pinned, unmodified PsyCross headers
confirmed a 20-byte display environment, `isinter` at offset 16, and
`isrgb24` at offset 17. The check disabled extended host primitive pointers.
It compiled no SDK body and did not resume the stopped PsyCross build.
The check and its executable stay under `build/analysis/`.

The existing [SetDefDispEnv note](call-8008abbc.md) already records zero
stores at both offsets. No body was entered again for this correction.
The game then writes whether mode equals 3 to offset 17. Its interlace
field remains at the SDK default of zero. The recorded boot mode is 2,
so both flags are zero on this boot.

Our `DisplayEnvironment` now keeps separate interlace and RGB24 fields.
The buffer advance sets the RGB24 field and retains the default interlace
value. The host renderer rejects unsupported RGB24 and interlaced views
separately. The state test checks mode 3 enables RGB24 without enabling
interlace, and mode 2 leaves both off. This fixes the native model and
its tests; it does not establish full SDK or retail behavior verification.
