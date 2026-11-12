# SPDX-License-Identifier: GPL-3.0-or-later
"""Extract an ISO9660 tree from a MODE2/2352 BIN/CUE.

    python tools/disc.py path/to/game.cue
    python tools/disc.py path/to/game.cue --out build/disc

The cue path may be omitted when AM3D_DISC is set. Track 1 must be
MODE2/2352. User data is the 2048 bytes after the 12-byte sync, 4-byte
header, and 8-byte subheader.
"""

from __future__ import annotations

import argparse
import os
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
MODE2_RAW = 2352
ISO_SECTOR = 2048
# Sync, header, and subheader sit in front of the 2048-byte user data.
USER_OFFSET = 24
_INVALID = '<>:"|?*'
_RESERVED = {"CON", "PRN", "AUX", "NUL"}


class DiscError(Exception):
    pass


class Track:
    def __init__(self, number: int, mode: str, path: Path, file_type: str) -> None:
        self.number = number
        self.mode = mode
        self.path = path
        self.file_type = file_type
        self.indexes: dict[int, int] = {}


class Mode2Image:
    def __init__(self, path: Path, start: int, end: int) -> None:
        self.path = path
        self.start = start
        self.count = end - start
        self._fh = path.open("rb")

    def close(self) -> None:
        self._fh.close()

    def __enter__(self) -> Mode2Image:
        return self

    def __exit__(self, *args: object) -> None:
        self.close()

    def sector(self, lba: int) -> bytes:
        if lba < 0 or lba >= self.count:
            raise DiscError(f"sector {lba} is outside the data track")
        self._fh.seek((self.start + lba) * MODE2_RAW)
        raw = self._fh.read(MODE2_RAW)
        if len(raw) != MODE2_RAW:
            raise DiscError(f"short read at sector {lba}")
        return mode2_user_data(raw)


def parse_msf(text: str) -> int:
    parts = text.split(":")
    if len(parts) != 3:
        raise DiscError(f"bad MSF: {text}")
    try:
        minutes = int(parts[0])
        seconds = int(parts[1])
        frames = int(parts[2])
    except ValueError as exc:
        raise DiscError(f"bad MSF: {text}") from exc
    if minutes < 0 or not 0 <= seconds <= 59 or not 0 <= frames <= 74:
        raise DiscError(f"bad MSF: {text}")
    return minutes * 60 * 75 + seconds * 75 + frames


def mode2_user_data(sector: bytes) -> bytes:
    if len(sector) != MODE2_RAW:
        raise DiscError(f"MODE2 sector is {len(sector)} bytes, expected {MODE2_RAW}")
    return sector[USER_OFFSET:USER_OFFSET + ISO_SECTOR]


def _read_text(path: Path) -> str:
    data = path.read_bytes()
    if data.startswith(b"\xef\xbb\xbf"):
        data = data[3:]
    try:
        return data.decode("utf-8")
    except UnicodeDecodeError:
        return data.decode("latin-1")


def _parse_file_line(line: str, directory: Path) -> tuple[Path, str]:
    rest = line.strip()[4:].strip()
    if not rest:
        raise DiscError("bad cue FILE line")
    if rest[0] == '"':
        end = rest.find('"', 1)
        if end < 0:
            raise DiscError("unterminated quote in cue FILE line")
        name = rest[1:end]
        file_type = rest[end + 1:].strip().upper()
    else:
        bits = rest.split()
        if len(bits) < 2:
            raise DiscError("bad cue FILE line")
        name = bits[0]
        file_type = bits[-1].upper()
    if not name or not file_type:
        raise DiscError("bad cue FILE line")
    return directory / name, file_type


def parse_cue(path: Path) -> list[Track]:
    text = _read_text(path)
    tracks: list[Track] = []
    current_path: Path | None = None
    current_type = ""
    current: Track | None = None
    for raw in text.splitlines():
        line = raw.strip()
        if not line:
            continue
        head = line.split(None, 1)[0].upper()
        if head == "FILE":
            current_path, current_type = _parse_file_line(line, path.parent)
            current = None
            continue
        if head == "TRACK":
            if current_path is None:
                raise DiscError(f"TRACK before FILE: {line}")
            parts = line.split()
            if len(parts) < 3:
                raise DiscError(f"bad TRACK line: {line}")
            try:
                number = int(parts[1])
            except ValueError as exc:
                raise DiscError(f"bad TRACK line: {line}") from exc
            current = Track(number, parts[2].upper(), current_path, current_type)
            tracks.append(current)
            continue
        if head == "INDEX":
            if current is None:
                raise DiscError(f"INDEX before TRACK: {line}")
            parts = line.split()
            if len(parts) < 3:
                raise DiscError(f"bad INDEX line: {line}")
            try:
                which = int(parts[1])
            except ValueError as exc:
                raise DiscError(f"bad INDEX line: {line}") from exc
            current.indexes[which] = parse_msf(parts[2])
            continue
        # Cue sheets carry metadata lines (REM, FLAGS, CATALOG) we do not need.
    if not tracks:
        raise DiscError(f"no tracks in {path}")
    return tracks


def _open_track(track: Track, tracks: list[Track]) -> Mode2Image:
    if track.mode != "MODE2/2352":
        raise DiscError(f"track 1 is {track.mode}, expected MODE2/2352")
    if track.file_type != "BINARY":
        raise DiscError(f"track 1 file type is {track.file_type}, expected BINARY")
    if 1 not in track.indexes:
        raise DiscError("track 1 has no INDEX 01")
    if not track.path.is_file():
        raise DiscError(f"bin not found: {track.path}")
    size = track.path.stat().st_size
    if size % MODE2_RAW != 0:
        raise DiscError(f"bin size is not a multiple of {MODE2_RAW}: {track.path}")
    file_sectors = size // MODE2_RAW
    start = track.indexes[1]
    end = file_sectors
    later = [item for item in tracks if item.path == track.path and item.number > track.number]
    if later:
        nxt = min(later, key=lambda item: item.number)
        if 0 in nxt.indexes:
            end = nxt.indexes[0]
        elif 1 in nxt.indexes:
            end = nxt.indexes[1]
        else:
            raise DiscError(f"track {nxt.number} has no index")
    if start < 0 or end < start or end > file_sectors or end == start:
        raise DiscError("track 1 extent is outside the bin")
    return Mode2Image(track.path, start, end)


def _extent_fits(image: Mode2Image, lba: int, length: int) -> bool:
    # Mixed-mode discs list CDDA files at LBAs past track 1. Skip those.
    if lba < 0 or length < 0 or lba >= image.count:
        return False
    if length == 0:
        return True
    sectors = (length + ISO_SECTOR - 1) // ISO_SECTOR
    return lba + sectors <= image.count


def _read_extent(image: Mode2Image, lba: int, length: int) -> bytes:
    if length < 0 or length > image.count * ISO_SECTOR:
        raise DiscError(f"extent length {length} is outside the image")
    chunks: list[bytes] = []
    left = length
    sector = lba
    while left > 0:
        data = image.sector(sector)
        take = data[:left]
        chunks.append(take)
        left -= len(take)
        sector += 1
    return b"".join(chunks)


def _write_extent(image: Mode2Image, lba: int, length: int, dest: Path) -> None:
    if length < 0 or length > image.count * ISO_SECTOR:
        raise DiscError(f"extent length {length} is outside the image")
    dest.parent.mkdir(parents=True, exist_ok=True)
    left = length
    sector = lba
    with dest.open("wb") as out:
        while left > 0:
            data = image.sector(sector)
            take = data[:left]
            out.write(take)
            left -= len(take)
            sector += 1


def _iter_records(data: bytes):
    off = 0
    limit = len(data)
    while off < limit:
        if data[off] == 0:
            off = (off // ISO_SECTOR + 1) * ISO_SECTOR
            continue
        rec_len = data[off]
        if rec_len < 34 or off + rec_len > limit:
            raise DiscError("truncated directory record")
        name_len = data[off + 32]
        if 33 + name_len > rec_len:
            raise DiscError("directory name exceeds record")
        yield {
            "lba": int.from_bytes(data[off + 2:off + 6], "little"),
            "length": int.from_bytes(data[off + 10:off + 14], "little"),
            "flags": data[off + 25],
            "unit": data[off + 26],
            "gap": data[off + 27],
            "name": bytes(data[off + 33:off + 33 + name_len]),
        }
        off += rec_len


def _clean_name(raw: bytes, joliet: bool) -> str:
    # 0x00 and 0x01 are the current and parent directory, including on Joliet.
    if raw in (b"\x00", b"\x01"):
        return ""
    if joliet:
        if len(raw) % 2 == 1:
            raw = raw[:-1]
        text = raw.decode("utf-16-be", errors="replace")
    else:
        text = raw.decode("latin-1")
    text = text.split(";", 1)[0].rstrip(" ")
    if text.endswith("."):
        text = text[:-1]
    return text


def _sanitize(name: str) -> str:
    # Windows rejects these characters and device names in a path.
    cleaned = ["_" if ch in _INVALID or ord(ch) < 32 else ch for ch in name]
    name = "".join(cleaned).rstrip(" .")
    if not name or name in {".", ".."} or "/" in name or "\\" in name:
        raise DiscError("directory record has an empty name")
    stem = name.split(".", 1)[0].upper()
    if stem in _RESERVED or (len(stem) == 4 and stem[:3] in {"COM", "LPT"} and stem[3].isdigit()):
        name = "_" + name
    return name


def _safe_dest(root: Path, name: str) -> Path:
    dest = (root / name).resolve()
    base = root.resolve()
    if dest != base and base not in dest.parents:
        raise DiscError(f"refusing to write outside the output directory: {name}")
    return dest


def _find_root(image: Mode2Image) -> tuple[dict, bool]:
    pvd = None
    joliet = None
    last = min(image.count, 32)
    for lba in range(16, last):
        sec = image.sector(lba)
        if sec[1:6] != b"CD001":
            continue
        kind = sec[0]
        if kind == 255:
            break
        if kind == 1 and pvd is None:
            pvd = sec
        elif kind == 2 and joliet is None:
            # Joliet keeps the long names from the supplementary descriptor.
            escape = sec[88:120]
            if b"%/@" in escape or b"%/C" in escape or b"%/E" in escape:
                joliet = sec
    chosen = joliet if joliet is not None else pvd
    if chosen is None:
        raise DiscError("ISO9660 primary volume descriptor not found")
    block = int.from_bytes(chosen[128:130], "little")
    if block != ISO_SECTOR:
        raise DiscError(f"unsupported logical block size {block}")
    rec_len = chosen[156]
    if rec_len < 34 or 156 + rec_len > ISO_SECTOR:
        raise DiscError("volume descriptor has no root directory")
    records = list(_iter_records(chosen[156:156 + rec_len]))
    if len(records) != 1:
        raise DiscError("volume descriptor has no root directory")
    return records[0], joliet is not None


def extract_iso(image: Mode2Image, out: Path) -> list[str]:
    root, joliet = _find_root(image)
    try:
        out.mkdir(parents=True, exist_ok=True)
    except OSError as exc:
        raise DiscError(f"cannot create output directory: {out}") from exc
    out = out.resolve()
    found: list[str] = []
    seen: set[tuple[int, bool]] = set()

    def walk(record: dict, directory: Path, prefix: str) -> None:
        key = (record["lba"], joliet)
        if key in seen:
            raise DiscError(f"directory cycle at sector {record['lba']}")
        seen.add(key)
        data = _read_extent(image, record["lba"], record["length"])
        for rec in _iter_records(data):
            cleaned = _clean_name(rec["name"], joliet)
            if not cleaned:
                continue
            name = _sanitize(cleaned)
            is_dir = bool(rec["flags"] & 0x02)
            # Those flags mean the bytes are not one contiguous run of sectors.
            if not is_dir and (rec["unit"] or rec["gap"] or rec["flags"] & 0x80):
                raise DiscError(f"non-contiguous file is not supported: {name}")
            rel = f"{prefix}/{name}" if prefix else name
            dest = _safe_dest(directory, name)
            if not _extent_fits(image, rec["lba"], rec["length"]):
                continue
            if is_dir:
                dest.mkdir(parents=True, exist_ok=True)
                walk(rec, dest, rel)
            else:
                _write_extent(image, rec["lba"], rec["length"], dest)
                found.append(rel)

    walk(root, out, "")
    found.sort()
    return found


def extract_cue(cue_path: Path, out: Path) -> list[str]:
    tracks = parse_cue(cue_path)
    track1 = next((item for item in tracks if item.number == 1), None)
    if track1 is None:
        raise DiscError("cue has no track 1")
    image = _open_track(track1, tracks)
    try:
        return extract_iso(image, out)
    finally:
        image.close()


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description="Extract ISO9660 files from a MODE2/2352 BIN/CUE.")
    parser.add_argument("cue", nargs="?", help="Cue path. Defaults to the AM3D_DISC environment variable.")
    parser.add_argument("--out", type=Path, help="Output directory. Default: build/disc")
    args = parser.parse_args(argv)
    try:
        cue_text = args.cue or os.environ.get("AM3D_DISC")
        if not cue_text:
            raise DiscError("pass a cue path or set AM3D_DISC")
        cue_path = Path(cue_text)
        if not cue_path.is_file():
            raise DiscError(f"cue not found: {cue_path}")
        out = args.out if args.out is not None else ROOT / "build" / "disc"
        for rel in extract_cue(cue_path, out):
            print(rel)
        return 0
    except DiscError as exc:
        print(f"error: {exc}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    sys.exit(main())
