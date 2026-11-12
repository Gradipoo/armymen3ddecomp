# SPDX-License-Identifier: GPL-3.0-or-later
"""Import a PS-X EXE into a local Ghidra project.

Strip the 2048-byte header and import the text as MIPS:LE:32:default
at the header load address. The project is tools/ghidra/project.
ExportFunctions.java writes docs/research/re/game-functions.tsv.

    python tools/ghidra/import.py path/to/SLUS

Decompile one function after that import. This runs DecompileAt.java
with -process and -noanalysis when the Ghidra project already exists.
OUT is a path you choose. If you omit it, the file lands under build/ghidra/.

    python tools/ghidra/import.py --decompile ADDR out.c
"""

from __future__ import annotations

import argparse
import os
import shutil
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
HEADER_SIZE = 0x800
MAGIC = b"PS-X EXE"
PROJECT_DIR = ROOT / "tools" / "ghidra" / "project"
PROJECT_NAME = "am3d"
SCRIPT_DIR = ROOT / "tools" / "ghidra" / "scripts"
TSV_PATH = ROOT / "docs" / "research" / "re" / "game-functions.tsv"
EXE_DIR = ROOT / "build" / "exe"
DECOMP_DIR = ROOT / "build" / "ghidra"
PROGRAM_MARK = EXE_DIR / "program.name"


class ToolError(Exception):
    pass


def _launcher_names() -> list[str]:
    names = ["analyzeHeadless"]
    if sys.platform == "win32":
        names.append("analyzeHeadless.bat")
    return names


def _from_support(support: Path) -> Path | None:
    for name in _launcher_names():
        candidate = support / name
        if candidate.is_file():
            return candidate
    return None


def _under(root: Path, depth: int, seen: set[Path]) -> Path | None:
    try:
        resolved = root.resolve()
    except OSError:
        return None
    if resolved in seen or depth < 0 or not root.exists():
        return None
    seen.add(resolved)
    found = _from_support(root / "support")
    if found is not None:
        return found
    if depth == 0 or not root.is_dir():
        return None
    try:
        children = list(root.iterdir())
    except OSError:
        return None
    for child in children:
        if not child.is_dir():
            continue
        found = _under(child, depth - 1, seen)
        if found is not None:
            return found
    return None


def _common_roots() -> list[Path]:
    roots: list[Path] = []
    if sys.platform == "darwin":
        roots.extend(
            [
                Path("/opt/homebrew/Caskroom/ghidra"),
                Path("/usr/local/Caskroom/ghidra"),
                Path("/opt/homebrew/opt/ghidra"),
                Path("/usr/local/opt/ghidra"),
                Path("/opt/homebrew/share/ghidra"),
                Path("/usr/local/share/ghidra"),
            ]
        )
    elif sys.platform == "win32":
        for key in ("ProgramFiles", "ProgramFiles(x86)", "ProgramW6432"):
            value = os.environ.get(key)
            if not value:
                continue
            base = Path(value)
            if not base.is_dir():
                continue
            try:
                roots.extend(base.glob("ghidra*"))
                roots.extend(base.glob("Ghidra*"))
            except OSError:
                continue
    else:
        roots.extend([Path("/opt/ghidra"), Path("/usr/share/ghidra")])
        for base in (Path("/opt"), Path("/usr/share")):
            if not base.is_dir():
                continue
            try:
                roots.extend(base.glob("ghidra*"))
                roots.extend(base.glob("Ghidra*"))
            except OSError:
                continue
    return roots


def find_analyze_headless() -> Path | None:
    install = os.environ.get("GHIDRA_INSTALL_DIR", "").strip().strip('"')
    if install:
        found = _from_support(Path(install) / "support")
        if found is not None:
            return found
    for name in _launcher_names():
        found = shutil.which(name)
        if found:
            return Path(found)
    seen: set[Path] = set()
    for root in _common_roots():
        found = _under(root, 4, seen)
        if found is not None:
            return found
    return None


def install_hint() -> str:
    if sys.platform == "darwin":
        return (
            "Ghidra not found. Install it with Homebrew "
            "(brew install --cask ghidra), or set GHIDRA_INSTALL_DIR "
            "to the folder that contains support/analyzeHeadless."
        )
    if sys.platform == "win32":
        return (
            "Ghidra not found. Install it from https://ghidra-sre.org/ "
            "under Program Files, or set GHIDRA_INSTALL_DIR to the folder "
            "that contains support\\analyzeHeadless.bat."
        )
    return (
        "Ghidra not found. Install it from https://ghidra-sre.org/ "
        "into /opt/ghidra or /usr/share/ghidra, or set GHIDRA_INSTALL_DIR "
        "to the folder that contains support/analyzeHeadless."
    )


def run_command(args: list[str]) -> int:
    # CreateProcess will not launch a .bat path. cmd parses this quoted command line.
    if args and args[0].lower().endswith(".bat"):
        completed = subprocess.run(subprocess.list2cmdline(args), shell=True, cwd=ROOT)
    else:
        completed = subprocess.run(args, cwd=ROOT)
    return completed.returncode


def read_exe(path: Path) -> tuple[int, bytes]:
    if not path.is_file():
        raise ToolError(f"file not found: {path}")
    data = path.read_bytes()
    if len(data) < 0x20 or data[:8] != MAGIC:
        raise ToolError(f"not a PS-X EXE: {path}")
    load = int.from_bytes(data[0x18:0x1C], "little")
    size = int.from_bytes(data[0x1C:0x20], "little")
    if len(data) < HEADER_SIZE:
        raise ToolError("PS-X EXE header is truncated")
    if len(data) < HEADER_SIZE + size:
        raise ToolError(f"text size 0x{size:x} exceeds the file (header is {HEADER_SIZE} bytes)")
    return load, data[HEADER_SIZE:HEADER_SIZE + size]


def _normalize_addr(text: str) -> str:
    raw = text.strip()
    if raw.lower().startswith("0x"):
        raw = raw[2:]
    try:
        return f"{int(raw, 16):08x}"
    except ValueError as exc:
        raise ToolError(f"bad address: {text}") from exc


def _require_headless() -> Path:
    headless = find_analyze_headless()
    if headless is None:
        raise ToolError(install_hint())
    return headless


def decompile(addr_text: str, out: Path | None) -> int:
    gpr = PROJECT_DIR / f"{PROJECT_NAME}.gpr"
    if not gpr.is_file() or not PROGRAM_MARK.is_file():
        raise ToolError("Ghidra project not found. Import the executable first.")
    program = PROGRAM_MARK.read_text(encoding="utf-8").strip()
    if not program:
        raise ToolError("Ghidra project not found. Import the executable first.")
    addr = _normalize_addr(addr_text)
    if out is None:
        out = DECOMP_DIR / f"{addr}.c"
    elif not out.is_absolute():
        out = Path.cwd() / out
    out = out.resolve()
    headless = _require_headless()
    out.parent.mkdir(parents=True, exist_ok=True)
    cmd = [
        str(headless),
        str(PROJECT_DIR),
        PROJECT_NAME,
        "-process",
        program,
        "-noanalysis",
        "-scriptPath",
        str(SCRIPT_DIR),
        "-postScript",
        "DecompileAt.java",
        addr,
        str(out),
    ]
    return run_command(cmd)


def import_exe(exe: Path) -> int:
    if not exe.is_file():
        raise ToolError(f"file not found: {exe}")
    load, text = read_exe(exe)
    headless = _require_headless()
    EXE_DIR.mkdir(parents=True, exist_ok=True)
    text_path = EXE_DIR / f"{exe.name}.text"
    text_path.write_bytes(text)
    PROGRAM_MARK.write_text(text_path.name + "\n", encoding="utf-8")
    TSV_PATH.parent.mkdir(parents=True, exist_ok=True)
    PROJECT_DIR.mkdir(parents=True, exist_ok=True)
    cmd = [
        str(headless),
        str(PROJECT_DIR),
        PROJECT_NAME,
        "-import",
        str(text_path),
        "-processor",
        "MIPS:LE:32:default",
        "-loader",
        "BinaryLoader",
        "-loader-baseAddr",
        f"0x{load:08x}",
        "-overwrite",
        "-scriptPath",
        str(SCRIPT_DIR),
        "-postScript",
        "ExportFunctions.java",
        str(TSV_PATH),
    ]
    print(f"load=0x{load:08x}")
    return run_command(cmd)


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        description="Import a PS-X EXE into Ghidra, or decompile one address.",
        epilog=(
            "examples:\n"
            "  python tools/ghidra/import.py path/to/SLUS\n"
            "  python tools/ghidra/import.py --decompile ADDR out.c"
        ),
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )
    parser.add_argument("exe", nargs="?", help="Path to a PS-X EXE.")
    parser.add_argument(
        "--decompile",
        nargs="+",
        metavar=("ADDR", "OUT"),
        help="Decompile ADDR to OUT. OUT defaults to build/ghidra/ADDR.c.",
    )
    args = parser.parse_args(argv)
    try:
        if args.decompile and args.exe:
            raise ToolError("pass an executable or --decompile, not both")
        if args.decompile:
            if len(args.decompile) > 2:
                raise ToolError("usage: --decompile ADDR [OUT]")
            out = Path(args.decompile[1]) if len(args.decompile) == 2 else None
            return decompile(args.decompile[0], out)
        if not args.exe:
            parser.print_help(sys.stderr)
            return 2
        return import_exe(Path(args.exe))
    except ToolError as exc:
        print(f"error: {exc}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    sys.exit(main())
