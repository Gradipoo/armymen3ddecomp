# DATA/FRONT.TIM

Measured on the owner's USA disc extract. The file stays in `build/disc/DATA/FRONT.TIM`. It is not committed. The public test uses a synthetic byte string with the same field order.

The file is 2880 bytes.

| Offset | Word | Meaning in this file |
| --- | --- | --- |
| 0 | `0x00000010` | File mark |
| 4 | `0x00000008` | 4-bit pixels and a color table. Bits 0 to 2 are the depth. Bit 3 says the color table is present. |
| 8 | `0x0000002c` | Color-table block length, 44 bytes, including this word |
| 12 | halfwords `512`, `506`, `16`, `1` | Color-table position and size. Sixteen colors, one row. |
| 20 | first color `0x5335` | Fifteen-bit colors. One entry is `0`. Bit 15 is clear on every entry in this file. |
| 52 | `0x00000b0c` | Pixel-block length, 2828 bytes, including this word |
| 56 | halfwords `640`, `0`, `11`, `128` | Pixel-block position and size. `11` counts 16-bit words per row, not pixels. |
| 64 | 2816 pixel bytes | `11 * 2 * 128`. The block ends at the end of the file. |

Each pixel word holds four indices. The low nibble is the left pixel. The next nibble is the next pixel to the right. A row is `11 * 4 = 44` pixels. The picture is 44 by 128.

A color-table value of `0` is not stored. In this file that entry is the only zero, and its high bit is clear. Every other entry is stored with the high bit masked off. The stored value is the 15-bit color already used by the fill sink.

The halfwords at offset 56 place the pixel block at VRAM x `640`, y `0`. The halfwords at offset 12 place the color table at VRAM x `512`, y `506`. This change does not upload either block as a GPU texture. `components/platform/fill_vram.cpp` still rejects every GPU packet other than the three-word fill. The smoke window copies the decoded pixels into the current drawing page at x `234`, y `56` relative to that page's origin, so the 44 by 128 picture sits inside the 512 by 240 view.

The reader accepts this field order for any size whose block lengths match the rectangles. It rejects a file mark other than `0x10`, a flag other than `0x8`, a byte length that does not match the two blocks, and a position halfword above x `1023` or y `511`.

The later [upload observation](front-tim-upload-observation.md) matched
all 2880 live RAM bytes to this file at LoadImage entry while preparing
the observed menu. Native texture submission and screen placement remain
separate from this file-layout reader.

## Native upload service

`components/platform/front_tim.cpp` now provides `upload_front_tim` with a
caller-provided image-upload sink. It decodes the measured block layout
into palette and packed pixel words, then calls the sink in that order.
Rectangle fields cite offsets 12 and 56. Bit 15 is preserved in both blocks;
this path does not decode texel indices or use `FillVram::write_pixel`.

Both blocks and their lengths are validated before either call. Zero-sized
or wrapping VRAM rectangles reject, as do truncated or extra bytes. Both
word arrays are decoded before submission. Sink exceptions propagate and
can leave the first upload submitted; this is not rollback semantics.
The existing `paint_front_tim` decoded display path remains available.

Synthetic public checks cover exact word transport including bit 15,
submission order, invalid second blocks with no calls, rectangle bounds,
length overflow, truncation, and null input/sink. Default and SDL2 builds
passed the focused checks. The SDL2 fill and platform tests also passed.

A local integration sent the owner's file through this native API into the
unchanged local GPU candidate's actual GP0 image-transfer parser. It emitted
palette `(512,506,16,1)` and pixels `(640,0,11,128)` and compared all 1424
resulting VRAM words with the file. There were zero mismatches. Source,
commands, hashes, dependency records and logs remain under
`build/coordination/native-front-integration/`. The local GPU dependency is
not adopted; the default build gains no third-party runtime dependency.
This is a texture-upload connection, not a reconstructed menu frame or
update loop. The smoke window's existing placement remains a stand-in.
