# SPDX-License-Identifier: GPL-3.0-or-later
"""Compile preprocessed C with explicit local tools. Downloads nothing.

Writes assembly, object code, logs, and a provenance record to build/compile/.
These files stay local. The default flags are a starting point, not a claim
about the compiler settings used by Army Men 3D.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
FLAGS = ['-O2', '-G0', '-mips1', '-mcpu=3000', '-msoft-float',
         '-mno-abicalls', '-fgnu-linker', '-quiet']


def digest(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def compile_candidate(source: Path, cc1: Path, maspsx: Path, assembler: Path,
                      aspsx_version: str, flags: list[str], out: Path) -> dict:
    source, cc1, maspsx, assembler = [p.resolve() for p in (source, cc1, maspsx, assembler)]
    out = out.resolve()
    outputs = [out / name for name in ('compiler.s', 'assembler.s', 'candidate.o',
                                       'compiler.log', 'adapter.log', 'assembler.log',
                                       'provenance.json')]
    # Guard every path before deleting any old output or opening stage logs.
    for output in outputs:
        for supplied in (source, cc1, maspsx, assembler):
            if output.resolve() == supplied or (output.exists() and supplied.exists()
                                                and output.samefile(supplied)):
                raise ValueError(f'input/tool collides with an output path: {supplied}')
    out.mkdir(parents=True, exist_ok=True)
    for output in outputs:
        output.unlink(missing_ok=True)
    manifest = out / 'provenance.json'
    obj = out / 'candidate.o'
    if source.suffix != '.i':
        raise ValueError('input must be preprocessed C in an .i file')
    for path in (source, cc1, maspsx, assembler):
        if not path.is_file():
            raise ValueError(f'file not found: {path}')
    raw = out / 'compiler.s'
    adapted = out / 'assembler.s'
    commands = [
        [str(cc1), *flags, str(source), '-o', str(raw)],
        [sys.executable, str(maspsx), f'--aspsx-version={aspsx_version}'],
        [str(assembler), '-triple=mipsel-none-elf', '-mcpu=mips1', '-filetype=obj',
         str(adapted), '-o', str(obj)],
    ]
    inputs = {'source': digest(source), 'cc1': digest(cc1), 'llvm_mc': digest(assembler)}
    # The adapter imports Python modules next to its entry point.
    inputs['maspsx_python_files'] = {
        path.relative_to(maspsx.parent).as_posix(): digest(path)
        for path in sorted(maspsx.parent.rglob('*.py'))
    }
    with (out / 'compiler.log').open('wb') as log:
        subprocess.run(commands[0], stdin=subprocess.DEVNULL, stdout=log, stderr=log, check=True)
    with raw.open('rb') as stdin, adapted.open('wb') as stdout, (out / 'adapter.log').open('wb') as log:
        subprocess.run(commands[1], stdin=stdin, stdout=stdout, stderr=log, check=True)
    with (out / 'assembler.log').open('wb') as log:
        subprocess.run(commands[2], stdin=subprocess.DEVNULL, stdout=log, stderr=log, check=True)
    record = {'source': str(source), 'input_sha256': inputs, 'commands': commands,
              'aspsx_version': aspsx_version, 'compiler_flags': flags,
              'object': str(obj), 'object_sha256': digest(obj)}
    manifest.write_text(json.dumps(record, indent=2) + '\n', encoding='utf-8')
    return record


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('source', type=Path)
    parser.add_argument('--cc1', type=Path, required=True)
    parser.add_argument('--maspsx', type=Path, required=True)
    parser.add_argument('--llvm-mc', type=Path, required=True)
    parser.add_argument('--aspsx-version', required=True)
    parser.add_argument('--compiler-flag', action='append',
                        help='Replace the default flag list. Repeat as --compiler-flag=-O2, etc.')
    args = parser.parse_args(argv)
    try:
        result = compile_candidate(args.source, args.cc1, args.maspsx, args.llvm_mc,
                                   args.aspsx_version,
                                   args.compiler_flag if args.compiler_flag is not None else FLAGS,
                                   ROOT / 'build' / 'compile')
    except (OSError, ValueError, subprocess.CalledProcessError) as exc:
        print(f'error: {exc}', file=sys.stderr)
        return 1
    print(f'Candidate object: {result["object"]}')
    print('Local commands, hashes, and flags: build/compile/provenance.json')
    return 0


if __name__ == '__main__':
    sys.exit(main())
