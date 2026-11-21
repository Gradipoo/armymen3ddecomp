# SPDX-License-Identifier: GPL-3.0-or-later
"""Summarize a local ALP1 PCSX observation run for checklist fill.

    python3 tools/alp1_observation_summarize.py <run-dir>

Does not commit output. Procedure: docs/research/re/prototype-alp1-movement-observation.md
"""

from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

FRAME_RE = re.compile(r"^frame-(\d{6})\.ppm$")


def main() -> int:
    parser = argparse.ArgumentParser(description="Summarize ALP1 observation run dir")
    parser.add_argument("run_dir", type=Path, help="build/coordination/.../<run-id>")
    args = parser.parse_args()
    run_dir = args.run_dir.resolve()
    if not run_dir.is_dir():
        print(f"error: not a directory: {run_dir}", file=sys.stderr)
        return 2

    frames_dir = run_dir / "frames"
    pad_log = run_dir / "pad-input.tsv"
    session = run_dir / "session.txt"
    checklist = run_dir / "checklist.tsv"

    frame_nums: list[int] = []
    if frames_dir.is_dir():
        for path in frames_dir.iterdir():
            m = FRAME_RE.match(path.name)
            if m:
                frame_nums.append(int(m.group(1)))
    frame_nums.sort()

    pad_lines = 0
    if pad_log.is_file():
        pad_lines = sum(1 for ln in pad_log.read_text(encoding="utf-8").splitlines() if ln.strip())

    print(f"run_dir: {run_dir}")
    print(f"frames: {len(frame_nums)}")
    if frame_nums:
        print(f"frame_range: {frame_nums[0]:6d} .. {frame_nums[-1]:6d}")
        tail = frame_nums[-3:]
        paths = [str(frames_dir / f"frame-{n:06d}.ppm") for n in tail]
        print("latest_frames:")
        for p in paths:
            print(f"  {p}")
    print(f"pad_input_lines: {pad_lines}")
    if pad_lines <= 1:
        print("note: pad-input.tsv is empty or only the initial line.")
        print("      guest pad logging needs controller input mapped to pad 1 in PCSX.")

    for label, path in (
        ("session", session),
        ("checklist", checklist),
    ):
        print(f"{label}_present: {path.is_file()}")

    print()
    print("next:")
    print(f"  python3 tools/alp1_observation_checklist.py validate {run_dir}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())