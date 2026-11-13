# R03: SDK name provenance

Status: Passed provenance trial. Reviewed November 13, 2026.
See the [result](results/sdk-provenance.md). No new names were accepted.

## Question and scope

Can every accepted SDK name be traced to its inputs, with ambiguous leads
kept separate? Review `tools/sdk_scan.py`, `tools/sdk_match.py`, and
`docs/research/re/sdk.md`. The existing agreement across signature versions
does not identify the linked SDK version. Study [psy-q-decomp's declared
3.5 target](https://github.com/sozud/psy-q-decomp/blob/bda8aa2a39b2b91f4aa87173a2966b9ed285d534/README.md)
without entering a named SDK body.

Permitted public file: `docs/workers/results/sdk-provenance.md`.
Permitted local directory: `build/research/sdk/`.
Do not edit SDK tables or import signature bytes. Read `docs/WORKERS.md`.

## Inputs and commands

```
python3 -m unittest discover -s tests -p 'test_sdk_*.py' -v
python3 tools/sdk_scan.py LOCAL_EXE LOCAL_SIGNATURE_DIRECTORY
python3 tools/sdk_match.py LOCAL_EXE
python3 tools/pr_guard.py
```

Capture scan output locally. Use only the existing local signature checkout.
Record its actual revision, directory layout and file hashes in the local
manifest. If the checkout or EXE is absent, complete the synthetic phase
and mark the retail phase Blocked. Do not fetch SDK archives.

## Acceptance and evidence

Create synthetic signatures for an exact hit, masked hit, internal label,
two names at one address, same name at two addresses, and the same match
repeated in different versions. Run the current scanner on a synthetic
EXE. Count fixed bytes, total bytes, wildcard density, locations per
signature, competing names per address, and distinct source signatures.
Record which properties the present output loses. No probabilistic
confidence percentage is justified by a mask length alone.

Propose a local provenance schema that preserves source revision, file,
record index, signature digest, label offset, version set, match count,
and decision reason. Distinguish table names, pattern hits, ambiguous
leads, and externally confirmed names. Suggest a reproducible regeneration
check for `sdk_names.txt` without changing it in this task.

For the retail phase, reproduce existing counts and list count differences
only. Do not invent a reason for a difference or promote names. Check the
signature repository's license declaration. If none is present, report
that fact. Public availability alone is not permission to import files.

## Known failure modes

Shared SDK wrappers can match multiple versions. A label can point inside
a routine. Signature aliases need not mean different functions. Version
directories are source labels, not independent statistical observations.
SDK names avoid repeated tracing; they do not establish a game compiler.
