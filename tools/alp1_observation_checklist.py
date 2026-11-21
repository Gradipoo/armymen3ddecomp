# SPDX-License-Identifier: GPL-3.0-or-later
"""ALP1 movement observation checklist under build/coordination/.

    python3 tools/alp1_observation_checklist.py init <run-dir>
    python3 tools/alp1_observation_checklist.py show <run-dir>
    python3 tools/alp1_observation_checklist.py validate <run-dir>
    python3 tools/alp1_observation_checklist.py self-test

Procedure: docs/research/re/prototype-alp1-movement-observation.md
"""

from __future__ import annotations

import argparse
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
DRY_RUN = ROOT / "build" / "coordination" / "alp1-movement-observation" / "_dry_run"

HEADER = [
    "Run id",
    "Date",
    "Reach ALP1 (Y/N)",
    "Spawn sanity vs PAD 50 / 1252 / 50",
    "After-sequence position notes",
    "Capture paths",
]


def _tsv_line(cells: list[str]) -> str:
    return "\t".join(cells) + "\n"


def init_run(run_dir: Path) -> None:
    run_dir = run_dir.resolve()
    run_dir.mkdir(parents=True, exist_ok=True)
    checklist = run_dir / "checklist.tsv"
    run_id = run_dir.name
    body = _tsv_line(HEADER)
    if not checklist.is_file():
        body += _tsv_line([run_id, "", "", "", "", ""])
    else:
        text = checklist.read_text(encoding="utf-8")
        lines = [ln for ln in text.splitlines() if ln.strip()]
        if not lines:
            body += _tsv_line([run_id, "", "", "", "", ""])
        elif lines[0].split("\t") != HEADER:
            body += _tsv_line([run_id, "", "", "", "", ""])
        else:
            body = text if text.endswith("\n") else text + "\n"
            if len(lines) == 1:
                body += _tsv_line([run_id, "", "", "", "", ""])
    checklist.write_text(body, encoding="utf-8")


def show_run(run_dir: Path) -> int:
    run_dir = run_dir.resolve()
    checklist = run_dir / "checklist.tsv"
    if not checklist.is_file():
        print(f"{checklist}: missing", file=sys.stderr)
        return 1
    text = checklist.read_text(encoding="utf-8")
    for line in text.splitlines():
        if not line.strip():
            continue
        cells = line.split("\t")
        if cells == HEADER:
            print(line)
            continue
        if any(cell.strip() for cell in cells):
            print(line)
    return 0


def validate_run(run_dir: Path) -> int:
    run_dir = run_dir.resolve()
    session = run_dir / "session.txt"
    if not session.is_file():
        print(f"validate: missing session.txt in {run_dir}", file=sys.stderr)
        print(
            "Run tools/pcsx/run_alp1_observation.sh or create session.txt before validate.",
            file=sys.stderr,
        )
        return 1
    checklist = run_dir / "checklist.tsv"
    if not checklist.is_file():
        print(f"validate: missing checklist.tsv in {run_dir}", file=sys.stderr)
        print("Run: python3 tools/alp1_observation_checklist.py init", file=sys.stderr)
        return 1
    frames = run_dir / "frames"
    if frames.is_dir():
        count = sum(1 for p in frames.iterdir() if p.is_file())
        print(f"validate: ok ({run_dir}); frames/ has {count} file(s)")
    else:
        print(f"validate: ok ({run_dir}); frames/ not present yet (optional)")

    pad_log = run_dir / "pad-input.tsv"
    if pad_log.is_file():
        pad_lines = [line for line in pad_log.read_text(encoding="utf-8").splitlines() if line.strip()]
        if len(pad_lines) <= 1:
            print(
                "validate: warn pad-input.tsv has no guest pad edges; map keyboard or "
                "controller to pad 1 in PCSX",
                file=sys.stderr,
            )
    return 0


def dry_session_stub(run_dir: Path) -> None:
    run_dir.mkdir(parents=True, exist_ok=True)
    session = run_dir / "session.txt"
    if session.is_file():
        return
    run_id = run_dir.name
    session.write_text(
        "\n".join(
            [
                f"run_id: {run_id}",
                "repo_commit: dry-run",
                "uname: self-test",
                "disc_cue:",
                "emulator_path:",
                "emulator_version:",
            ]
        )
        + "\n",
        encoding="utf-8",
    )


def self_test() -> int:
    dry_session_stub(DRY_RUN)
    init_run(DRY_RUN)
    return validate_run(DRY_RUN)


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    sub = parser.add_subparsers(dest="command", required=True)

    p_init = sub.add_parser("init", help="Create or refresh checklist.tsv in a run directory")
    p_init.add_argument("run_dir", type=Path)

    p_show = sub.add_parser("show", help="Print checklist rows that have any filled cell")
    p_show.add_argument("run_dir", type=Path)

    p_val = sub.add_parser("validate", help="Require session.txt; report optional frames/")
    p_val.add_argument("run_dir", type=Path)

    sub.add_parser("self-test", help="init + validate build/.../_dry_run")

    args = parser.parse_args(argv)
    if args.command == "init":
        init_run(args.run_dir)
        print(f"init: {args.run_dir.resolve() / 'checklist.tsv'}")
        return 0
    if args.command == "show":
        return show_run(args.run_dir)
    if args.command == "validate":
        return validate_run(args.run_dir)
    if args.command == "self-test":
        code = self_test()
        if code == 0:
            print(f"self-test: ok ({DRY_RUN})")
        return code
    return 1


if __name__ == "__main__":
    raise SystemExit(main())