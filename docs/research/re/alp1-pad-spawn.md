# ALP1.PAD player spawn (pad index 1)

Owner `build/disc/DATA/ALP1.PAD` on the measured machine is 8192 bytes
(`0x2000`). This note cites layout for prototype pad index **1** only
(`PAD ambusha 1` in `ALP1.TXT`). It does not implement a full PAD editor or
MAP/MDL tie-in.

## Header (bytes `0x0` .. `0x1f`)

| Offset | Dword (LE) | Role in this note |
| --- | --- | --- |
| `0x0` | `0x00000001` | Format id |
| `0x8` | `0x00002000` | File size cite |
| `0xc` | `0x00000020` | Record table starts at byte `0x20` |
| `0x18` | `0x00000004` | Dwords per pad record (stride `0x10`) |

## Pad record stride

Records begin at `0x20`. Stride is `0x10` bytes (four little-endian dwords).
Pad index `N` (1-based, matching TXT) starts at `0x20 + (N - 1) * 0x10`.

## Pad index 1 fields (measured)

| Record offset | Source dword | Host field | Measured value |
| --- | --- | --- | --- |
| `0x0` | word at file `0x20` | `x` | low 16 bits → `50` |
| `0x4` | word at file `0x24` | `z` | low 16 bits → `1252` |
| `0x8` | word at file `0x28` | `heading` | low 16 bits → `50` |
| `0xc` | word at file `0x2c` | (unused here) | not loaded for spawn |

Tagged high bytes on `0xfff90032` and `0x00100032` are preserved in the
retail file. The host reader uses the low 16 bits for `x` and `heading` only.

## TXT index mapping

`ALP1.TXT` lists `PAD ambusha 1` for the first numbered pad. This slice
assumes TXT pad number equals the 1-based record index. Retail loader offset
rules beyond that single slot are not cited here.

## EXE loader strings (not disassembled)

`build/disc/SLUS_004.91` contains `%s%d.pad` and `.pad` (file offsets
`0xb05cc` and `0xb05d0`). Load address `0x80010000` with text offset `0x800`
yields virtual addresses `0x800afdcc` and `0x800afdd0`. `python3
tools/sdk_match.py` names PSX BIOS pad APIs only; no mission `.pad` parser
address is cited in this change.

Disc bytes for spawn load use `read_disc_data_file` with a `0x2000` byte cap
(same measured size as the table above). See [prototype-task-6.md](prototype-task-6.md).

## Host API

| Piece | Path |
| --- | --- |
| Parser | `components/exe/alp1_pad_spawn.hpp`, `alp1_pad_spawn.cpp` |
| Movement start | `components/exe/mission_movement_slice.hpp` |

Disc-free tests decode spawn from `alp1_pad_spawn_fixture.hpp` (pad index 1:
`x=50`, `z=1252`, `heading=50`). Retail-path tests and smokes call
`load_alp1_pad_spawn_from_disc_root` when `build/disc/DATA/ALP1.PAD` is present.

## Limits

- One pad slot (index 1) only.
- No collision, camera, or full pad table export.
- No retail gameplay compare for spawn use.