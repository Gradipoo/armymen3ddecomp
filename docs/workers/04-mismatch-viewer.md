# R04: Local mismatch inspection

Status: Passed objdiff synthetic trial. Reviewed November 13, 2026.
See the [result](results/mismatch-viewer.md). The asm-differ/LLVM path is
blocked by objdump argument compatibility. Review speed is unmeasured.

## Question and scope

Does an existing viewer explain register, scheduling, relocation and size
differences faster than the current byte report? Evaluate [asm-differ](https://github.com/simonlindholm/asm-differ/tree/0dd09af8f8008f1f880327cf0aca3b26d2562ea2)
first. Its raw-image mode fits our present inputs. [Objdiff v3.8.3](https://github.com/encounter/objdiff/releases/tag/v3.8.3)
is an alternative once trustworthy target objects exist. Neither score
replaces `tools/compare.py`.

Permitted public file: `docs/workers/results/mismatch-viewer.md`.
Permitted local directory: `build/research/diff/`.
No compiler flag changes and no retail inputs. Read `docs/WORKERS.md`.

## Inputs and commands

Create an isolated environment under the local task directory. Pin
asm-differ to the revision linked above. Record its source and dependency
licenses before running. Confirm CLI options with its pinned `--help`.
Use the upstream [settings example](https://github.com/simonlindholm/asm-differ/blob/0dd09af8f8008f1f880327cf0aca3b26d2562ea2/diff_settings.py):
set `baseimg` and `myimg` to the raw fixture paths, `arch` to `mipsel`,
and `objdump_executable` to the explicit installed MIPS-capable objdump.
The pinned source's `MIPSEL_SETTINGS` selects little endian and MIPS 3000.
Keep settings under the task folder.

```
python3 tools/compare.py --help
python3 -m unittest discover -s tests -p test_compare.py -v
build/research/diff/venv/bin/python -m pip freeze
build/research/diff/venv/bin/asm-differ --help
python3 tools/pr_guard.py
```

Run the viewer from its settings directory with `--no-pager --format plain`
at address zero for each raw fixture. Supply the fixture's full end address
as the second positional argument. Preserve the actual successful argument
list in the manifest. Leave immediate and address ignoring disabled.
No watch mode or automatic builds are needed in this first trial.

## Acceptance and evidence

Build original synthetic MIPS fixtures for identical bytes, a changed
register, a changed constant, an inserted instruction, and an unresolved
call relocation. Use `llvm-mc` or an existing MIPS GNU assembler. Keep
assembly and objects local. Create a synthetic PS-X EXE for our comparator.
Run both tools on each applicable case, using full intended lengths.

The identical case must pass exact comparison. Each altered same-size case
must fail exact comparison. The inserted instruction must trigger our size
rejection. An unresolved ELF relocation must remain rejected until linked.
The viewer may align or hide differences. Document exactly what it shows
for every case and whether it ignores relocations or register changes.
Measure time to locate the first cause with and without the viewer for
these fixed fixtures. State the small sample limit.

## Known failure modes

Host objdump may not support MIPS. LLVM and GNU objdump output formats can
differ. A PS-X EXE is not an original relocatable object. Do not fabricate
relocation metadata from retail bytes to satisfy a viewer. If setup fails
three times, retain the evidence and stop rather than writing a new viewer.
