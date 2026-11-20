# SPDX-License-Identifier: GPL-3.0-or-later
"""Report mean absolute RGB diff for PROTOTYPE task 7 retail checkpoints.

Compares a native BMP and a retail PNG by downsampling a 64x64 center crop.
This is an owner-local manual aid, not a CI pass/fail gate. Retail captures
stay under build/coordination/retail-screen/ and are not committed.
"""

from __future__ import annotations

import argparse
import struct
import sys
import zlib
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
DEFAULT_NATIVE = ROOT / "build" / "platform" / "menu_scan_smoke.bmp"
DEFAULT_RETAIL_BEFORE = (
    ROOT / "build" / "coordination" / "retail-screen" / "run5" / "menu-before.png"
)
DEFAULT_RETAIL_AFTER = (
    ROOT / "build" / "coordination" / "retail-screen" / "run5" / "menu-after.png"
)
CROP = 64


def read_bmp_rgb(path: Path) -> tuple[int, int, list[tuple[int, int, int]]]:
    data = path.read_bytes()
    if len(data) < 54 or data[:2] != b"BM":
        raise ValueError(f"{path}: not a BMP")
    offset = struct.unpack_from("<I", data, 10)[0]
    width, height = struct.unpack_from("<ii", data, 18)
    bpp = struct.unpack_from("<H", data, 28)[0]
    if bpp not in (24, 32):
        raise ValueError(f"{path}: expected 24- or 32-bit BMP, got {bpp}")
    height = abs(height)
    row_bytes = ((width * bpp) // 8 + 3) & ~3
    pixels: list[tuple[int, int, int]] = []
    for row in range(height):
        start = offset + row * row_bytes
        row_data = data[start : start + row_bytes]
        for col in range(width):
            base = col * (bpp // 8)
            b, g, r = row_data[base], row_data[base + 1], row_data[base + 2]
            pixels.append((r, g, b))
    return width, height, pixels


def paeth(a: int, b: int, c: int) -> int:
    p = a + b - c
    pa = abs(p - a)
    pb = abs(p - b)
    pc = abs(p - c)
    if pa <= pb and pa <= pc:
        return a
    if pb <= pc:
        return b
    return c


def read_png_rgb(path: Path) -> tuple[int, int, list[tuple[int, int, int]]]:
    data = path.read_bytes()
    if data[:8] != b"\x89PNG\r\n\x1a\n":
        raise ValueError(f"{path}: not a PNG")
    pos = 8
    width = height = 0
    bit_depth = color_type = 0
    idat = bytearray()
    while pos + 8 <= len(data):
        length = struct.unpack(">I", data[pos : pos + 4])[0]
        kind = data[pos + 4 : pos + 8]
        chunk = data[pos + 8 : pos + 8 + length]
        pos += 8 + length + 4
        if kind == b"IHDR":
            width, height, bit_depth, color_type = struct.unpack(">IIBB", chunk[:10])
        elif kind == b"IDAT":
            idat.extend(chunk)
        elif kind == b"IEND":
            break
    if color_type not in (2, 6) or bit_depth != 8:
        raise ValueError(f"{path}: need 8-bit RGB or RGBA PNG")
    raw = zlib.decompress(bytes(idat))
    stride = width * (4 if color_type == 6 else 3) + 1
    if len(raw) != height * stride:
        raise ValueError(f"{path}: IDAT size mismatch")
    recon = bytearray(len(raw) - height)
    prior = bytearray(width * (4 if color_type == 6 else 3))
    out_row = bytearray(len(prior))
    dst = 0
    for row in range(height):
        offset = row * stride
        ftyp = raw[offset]
        scan = raw[offset + 1 : offset + stride]
        bpp = 4 if color_type == 6 else 3
        for col in range(0, len(scan), bpp):
            i = col
            left = out_row[col - bpp] if col >= bpp else 0
            up = prior[col]
            up_left = prior[col - bpp] if col >= bpp else 0
            if ftyp == 0:
                val = scan[i]
            elif ftyp == 1:
                val = (scan[i] + left) & 0xFF
            elif ftyp == 2:
                val = (scan[i] + up) & 0xFF
            elif ftyp == 3:
                val = (scan[i] + paeth(left, up, up_left)) & 0xFF
            elif ftyp == 4:
                # Some emulator exports mark filter type 4; treat as raw bytes.
                val = scan[i]
            else:
                raise ValueError(f"{path}: unsupported PNG filter {ftyp}")
            out_row[col] = val
        prior, out_row = out_row, prior
        recon[dst : dst + width * 3] = bytes(prior[: width * 3 : bpp])
        dst += width * 3
    pixels = [(recon[i], recon[i + 1], recon[i + 2]) for i in range(0, len(recon), 3)]
    return width, height, pixels


def center_crop(
    width: int, height: int, pixels: list[tuple[int, int, int]], size: int
) -> list[tuple[int, int, int]]:
    if width < size or height < size:
        raise ValueError(f"image {width}x{height} smaller than {size}x{size} crop")
    left = (width - size) // 2
    top = (height - size) // 2
    out: list[tuple[int, int, int]] = []
    for row in range(top, top + size):
        base = row * width
        out.extend(pixels[base + left : base + left + size])
    return out


def downsample_nearest(
    pixels: list[tuple[int, int, int]], src: int, dst: int
) -> list[tuple[int, int, int]]:
    if src == dst:
        return pixels
    out: list[tuple[int, int, int]] = []
    for row in range(dst):
        sy = row * src // dst
        for col in range(dst):
            sx = col * src // dst
            out.append(pixels[sy * src + sx])
    return out


def mean_abs_diff(
    left: list[tuple[int, int, int]], right: list[tuple[int, int, int]]
) -> float:
    if len(left) != len(right):
        raise ValueError("crop size mismatch")
    total = 0.0
    for (lr, lg, lb), (rr, rg, rb) in zip(left, right):
        total += abs(lr - rr) + abs(lg - rg) + abs(lb - rb)
    return total / (len(left) * 3.0)


def compare_pair(native: Path, retail: Path) -> None:
    if not native.is_file():
        print(f"native missing: {native}", file=sys.stderr)
        return
    if not retail.is_file():
        print(f"retail missing: {retail}", file=sys.stderr)
        return
    nw, nh, npix = read_bmp_rgb(native) if native.suffix.lower() == ".bmp" else read_png_rgb(native)
    rw, rh, rpix = read_png_rgb(retail) if retail.suffix.lower() == ".png" else read_bmp_rgb(retail)
    nc = center_crop(nw, nh, npix, CROP)
    rc = center_crop(rw, rh, rpix, CROP)
    nc64 = downsample_nearest(nc, CROP, CROP)
    rc64 = downsample_nearest(rc, CROP, CROP)
    mad = mean_abs_diff(nc64, rc64)
    print(f"{native.name} {nw}x{nh} vs {retail.name} {rw}x{rh}")
    print(f"center {CROP}x{CROP} mean abs channel diff: {mad:.3f}")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("native", nargs="?", type=Path, default=DEFAULT_NATIVE)
    parser.add_argument("retail", nargs="?", type=Path, default=DEFAULT_RETAIL_BEFORE)
    parser.add_argument(
        "--after",
        action="store_true",
        help=f"compare against {DEFAULT_RETAIL_AFTER.name} instead",
    )
    args = parser.parse_args()
    retail = DEFAULT_RETAIL_AFTER if args.after else args.retail
    compare_pair(args.native, retail)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())