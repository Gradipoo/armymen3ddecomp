# Decompilation methods

Reviewed November 13, 2026. This page tracks local methods, their sources,
and the evidence needed to adopt them. [PLAN.md](PLAN.md) remains the
roadmap. [PROGRESS.md](PROGRESS.md) tracks game work. A tool trial cannot
promote a function to implemented or verified.

The immediate bottlenecks are incomplete types, provisional boundaries,
uncertain compiler settings, and scarce retail behavior evidence. The
1,869-entry Ghidra inventory is a starting point. It is not a list of
1,869 verified whole functions. The export records body address counts.
It does not prove that start plus size is a contiguous function range.

## Use existing tools first

| Need | Existing method | Decision and evidence |
| --- | --- | --- |
| Repeatable local preparation | [SOTN decompile.py](https://github.com/Xeeynamo/sotn-decomp/blob/b2350ec342ea498d0b838fdd19b6ed2dddc2595a/tools/decompile.py) combines context and m2c | Adapt the sequence, not its game types, source injection or cloud upload. Our helper is documented in [ANALYSIS.md](ANALYSIS.md). |
| Shared types | [m2c context](https://github.com/matt-kempster/m2c#usage) and [SOTN m2ctx](https://github.com/Xeeynamo/sotn-decomp/blob/b2350ec342ea498d0b838fdd19b6ed2dddc2595a/tools/m2ctx.py) | Test confirmed field widths, signedness, offsets and prototypes with [R01](workers/01-shared-context.md). Keep guesses separate. |
| Symbols and section boundaries | [spimdisasm](https://github.com/Decompollaborate/spimdisasm/blob/1.x/README.md) and [splat](https://github.com/ethteck/splat/blob/main/README.md) | Installed local versions are 1.42.4 and 0.50.1. One local range round trip passed. Full code/data and overlay maps remain unestablished. |
| Duplicate leads | [SOTN dups](https://github.com/Xeeynamo/sotn-decomp/blob/b2350ec342ea498d0b838fdd19b6ed2dddc2595a/tools/dups/src/main.rs) | Its MIPS key keeps the top six opcode bits and uses similarity. Such a score can prioritize review but cannot establish equality. Start with our smaller exact byte-window filter, then [R02](workers/02-boundaries-duplicates.md). |
| SDK leads | [Psy-Q signatures](https://github.com/lab313ru/psx_psyq_signatures) and [psy-q-decomp](https://github.com/sozud/psy-q-decomp/blob/bda8aa2a39b2b91f4aa87173a2966b9ed285d534/README.md) | Preserve existing named-call rules. Track signature provenance and ambiguity through [R03](workers/03-sdk-provenance.md). The latter project's declared 3.5 target does not identify our SDK version. |
| Explain mismatches | [asm-differ](https://github.com/simonlindholm/asm-differ/tree/0dd09af8f8008f1f880327cf0aca3b26d2562ea2), [objdiff](https://github.com/encounter/objdiff/tree/v3.8.3) | Trial raw-image inspection first through [R04](workers/04-mismatch-viewer.md). Objdiff compares relocatable objects. A target object and faithful relocations need evidence. Keep exact comparison authoritative for byte claims. |
| Compiler experiments | [old-gcc](https://github.com/decompals/old-gcc) and [maspsx](https://github.com/mkst/maspsx#known-differences) | Build a synthetic corpus through [R05](workers/05-compiler-corpus.md). Record compiler and assembler effects separately. Do not reopen the stopped display-fill experiment. |
| Retail behavior observations | [PCSX-Redux](https://github.com/pcsx-redux/pcsx-redux) | Evaluate local capture repeatability through [R06](workers/06-behavior-evidence.md). A host test or disassembly round trip does not establish retail behavior. |

These are method references. No other game's reconstructed logic or types
were imported. Optional tools remain separate from the portable runtime
and the disc-free checks. The tested environment and download hashes are
in [analysis-tools.json](analysis-tools.json).

## Evidence before a shared context

m2c supports repeated context files, limited cross-function inference,
inferred structure fields and stack-structure templates. Its context
parser expects preprocessed declarations. Its own README warns of limits
around preprocessing, bitfields, unions and inferred fields. Useful output
is still a draft. A wrong declaration can make a plausible result worse.
See the [upstream context description](https://github.com/matt-kempster/m2c#struct-field-inference).

Before a recovered type becomes shared context, record its address
evidence, field offsets, widths, signedness, alignment, pointer model and
confidence. Give a prototype an explicit unknown return type when callers
do not establish it. A return register that a caller ignores does not
prove a void return. Use fixed target widths rather than host `long` or
pointer size. Preserve unknown bytes as unknown bytes.

Keep each method trial's context under `build/research/`. A future shared
header needs a separately reviewed change with cited game evidence. Do
not turn m2c's inferred output or another game's header into our source.

[R01's synthetic trial](workers/results/shared-context.md) was executed by
a worker and independently reviewed on November 13, 2026. Correct context
resolved a pointer argument and two signed-halfword fields. The resulting
draft passed five layout checks and 121 host value cases. A wrong-width
context still exited zero without diagnostics and left unresolved fields.
The coordinator reproduced all three draft hashes and the host checks.
Five-run medians were 84.43 ms untyped and 91.79 ms typed. This trial
supports useful type integration, with no measured speed gain. Its manual
edit count fell from three to zero under a rule that excludes creating
and proving the context. Total effort savings remain unmeasured.

## Exact duplicate range filter

`tools/research_duplicates.py` is a small standard-library filter for the
current TSV. It does not replace spimdisasm's analysis or SOTN's broader
similarity search. It reads no assembly and changes no source or names.

```
python3 tools/research_duplicates.py build/disc/SLUS_004.91
python3 -m unittest discover -s tests -p test_research_duplicates.py -v
```

The report stays at `build/research/duplicates.json` by default. Use
`--out build/research/duplicates/leads.json` for the worker trial. Output
outside the real repository `build/` directory is rejected, including
symlink escapes. A failed rerun invalidates the previous report. Input
hashes and the local report let another run detect changed inputs.

The filter groups equal bytes in provisional start-plus-body-size windows.
It uses bytes as grouping keys, then records SHA-256 for provenance.
Different-size windows cannot group. The default minimum is 16 bytes.
Every window involved in an overlap is excluded, including nested ones.
Out-of-text and small windows are also excluded. Malformed inventory rows
and truncated EXEs fail the run. Nothing is masked, normalized or trimmed.

On November 13, 2026, eight synthetic tests passed. A local scan of the
current inventory considered 1,786 entries, excluded 83, and found 20
equal-window groups containing 82 entries. The report and its manifest
remain under `build/research/duplicates/`. No member's body was decoded
for this scan. These counts are prioritization leads, not functions saved
or verified behavior. Boundary review is still Pending under R02.

Even byte-identical routines at different PCs can call different targets
or load different data through relative addressing. Equal windows may
also be partial functions, stubs or data. Check named SDK entries first.
Never enter an already named SDK body to investigate a duplicate. A new
unnamed game body belongs in a separate one-gap task.

## Optional Ghidra body metadata

`tools/ghidra/scripts/ExportFunctionRanges.java` exports address-set metadata
without reading instructions or invoking the decompiler. It preserves the
existing three-column inventory. Run it from the repository root against
a local project copy with Ghidra's `-noanalysis -readOnly` options:

```
ANALYZE_HEADLESS LOCAL_PROJECT_COPY am3d -process SLUS_004.91.text -noanalysis -readOnly -scriptPath tools/ghidra/scripts -postScript ExportFunctionRanges.java build/analysis/function-ranges.json
python3 tools/research_function_ranges.py build/analysis/function-ranges.json build/disc/SLUS_004.91
python3 -m unittest discover -s tests -p test_research_function_ranges.py -v
```

Replace the launcher, project path and program name with the local values.
Use explicit local Ghidra log, settings, cache and temporary directories.
The tested worker command and Java properties stay in its local manifest.
Only the exporter itself is public. It restricts output to a `.json` file
inside the real repository `build/` directory and refuses to replace the
original imported image. A cancelled export leaves no completed report.

The validator requires a matching source-image SHA-256 and checks it
against the EXE or its declared text image. It also checks the inventory,
range lengths, entry membership, address space, overlaps and text bounds.
It reports when a single body range starts before its entry. A missing or
different inventory row makes the command return nonzero with a report.
Malformed metadata or a wrong source image fail without a success report.

This is a consistency check on Ghidra's current analysis. It cannot prove
that a range contains code, all return paths, or the required delay slots.
The source fingerprint identifies the original imported file, not the
current contents of project memory. Review a claimed function against
the owned executable before using it for a game change.

The exporter compiled and ran in Ghidra 12.2. The local metadata has 1,862
single-range bodies, five two-range bodies and two three-range bodies.
One single range begins before its function entry. The validator finds
1,861 eligible contiguous windows and seven discontiguous bodies. All
1,869 address/size/name records agree with the existing inventory and the
source fingerprint agrees with the EXE text image. These are observed
metadata facts, not confirmed whole-function boundaries. The original
project stayed unchanged, and repeated exports were byte-identical.

## Compiler and mismatch limits

maspsx documents version-dependent pseudo-instruction expansion, small-data
handling and hi/lo spacing. Its main path targets GNU `as`. Our tested
chain uses LLVM's assembler, so matching a simple fixture leaves wider
compatibility open. Preserve compiler assembly and adapter assembly as
separate local artifacts to locate where a difference first appears.
See [maspsx's stated design](https://github.com/mkst/maspsx#maspsx-aka-modern-aspsx)
and our [toolchain record](TOOLCHAIN.md).

Hold source, flags, symbol placement and adapter version constant while
comparing installed compilers on original synthetic fixtures. A future
retail corpus must use already researched whole game routines with
reviewed contiguous ranges. Do not use named SDK bodies as compiler
samples. Their provenance may differ from the game's compiler.

Use an aligned instruction display to explain a mismatch. A similarity
score is not an exact comparison. Unresolved relocations, missing delay
slots, smaller output ranges or padding cannot pass a full-range claim.
Never shorten the reference to match a candidate. Permutation is deferred
until the candidate semantics and a useful compiler setup are understood.
No cloud or distributed service may receive retail code.

### SDK provenance trial

[R03's reviewed audit](workers/results/sdk-provenance.md) reproduced all
383 existing named rows. The coordinator reran the unchanged production
scanner for all fourteen selected versions and rebuilt the ordered table
independently. The union has 203 ambiguous addresses. Only 39 accepted
rows have hits in every selected version; eighteen have hits in one.
The [SDK summary](research/re/sdk.md) now records the dated correction.
No matcher behavior or names changed.

The current scan output loses source file, record index, mask scope,
label offset and match multiplicity. Those fields are needed to review
aliases, internal labels and repeated signatures. The worker's local
provenance map traces the accepted rows to 2,461 source-label observations,
which are not independent confirmations. The signature checkout has no
reviewed license declaration. No signature files were imported.

The table branch of `sdk_match.py` checks an address against the loaded
image range. It does not freshly match that name's bytes. Treat table
names, current pattern hits, ambiguous leads and external confirmations
as separate evidence kinds in future provenance reports. Preserve the
current named-call rule and do not enter the named bodies again.

### Object-viewer trial

[R04's reviewed trial](workers/results/mismatch-viewer.md) found an existing
host-tool mismatch in asm-differ: its raw mode passes GNU binary flags
that LLVM rejects, and its ELF mode still passes an incompatible MIPS
architecture argument. Neither mode produced a diff with this host's LLVM
23.1.5. These are two recorded compatibility failures, not three failures
of every setup step combined. No wrapper or production viewer patch was
added.

The task's alternative, official native objdiff v3.8.3, passed six original
synthetic ELF object cases. It exposed changed registers, changed constants,
an inserted instruction, and call-relocation metadata. Its score was 100%
when an unresolved object was compared with itself. Our exact comparator
still rejected that object against a byte-identical raw reference because
the relocation was unresolved. Keep those two kinds of evidence separate.

The coordinator verified the official native release digest, checked
input and artifact hashes, and independently reproduced all six full JSON
views and exact-comparator outcomes. The optional binary and notices stay
under `build/research/diff/objdiff/`. It is not a runtime or baseline test
dependency. One example local command is:

```
build/research/diff/objdiff/objdiff-cli --no-color diff --target build/research/diff/fixtures/base.o --base build/research/diff/fixtures/register.o --output build/research/diff/register-review.json --format json-pretty fixture
```

Use trustworthy target objects with known symbol sizes and relocation
provenance. A PS-X EXE does not supply its original object metadata. Do
not invent relocations to satisfy a viewer. Human cause-location time,
scheduling coverage, the GUI and other hosts remain untested. No speed
gain is claimed.

### Failed-run output cleanup

R05's compiler setup failure exposed an unrelated bookkeeping problem in
`tools/compile_candidate.py`: a compiler-stage failure removed the object
and success record but left assembly and later-stage logs from a previous
run. Those files could be mistaken for outputs of the failed run.

The runner now clears all its known assembly, object, log and provenance
paths before starting a run. It first checks every supplied input and tool
against those output paths, including symlinks and hard links. A collision
fails before cleanup begins. The current failed-stage log is retained;
later stages do not run. Four fake-tool tests passed, including stale
output removal and preservation of colliding input/tool files. No old
compiler was invoked to test this change. This fix does not reopen the
stopped compiler corpus or establish any compiler-quality finding.

## Licenses and adoption

Reviewed upstream declarations are [MIT for spimdisasm](https://github.com/Decompollaborate/spimdisasm/blob/1.x/LICENSE),
[MIT for splat](https://github.com/ethteck/splat/blob/main/LICENSE),
[GPLv3 for m2c](https://github.com/matt-kempster/m2c/blob/master/LICENSE),
[Unlicense for asm-differ](https://github.com/simonlindholm/asm-differ/blob/main/LICENSE),
[MIT or Apache-2.0 for objdiff](https://github.com/encounter/objdiff#license),
and [MIT for psy-q-decomp](https://github.com/sozud/psy-q-decomp/blob/bda8aa2a39b2b91f4aa87173a2966b9ed285d534/LICENSE).
The selected m2c package identifies GPL-3.0-only. Review selected files and
dependency notices before importing or redistributing any tool code.
A public signature checkout or tool license does not license SDK archives.

The pinned asm-differ revision above is installed only in the local trial
environment. Objdiff v3.8.3 was the latest upstream release checked on this
date. SOTN and psy-q-decomp links pin reviewed repository snapshots. Recheck
an intended adoption against its actual source archive and license.

## Next batch

R01 through R04 have reviewed results. R05 stopped after three invalid-input
compiler failures and has no compiler comparison result. Its preparation contract is corrected
for a future separate assignment; the stopped batch stays stopped.
R06's tool discovery and protocol proposal are reviewed. Its PCSX-Redux
candidate is absent locally. Installed DuckStation help/version work with
desktop access; restricted-process startup failures were environmental.
No capture ran. Isolated configuration, explicit firmware identity and a
tested guest-debugger connection remain open prerequisites. See the
[R06 result](workers/results/behavior-evidence.md). The common worker contract is in
[WORKERS.md](WORKERS.md). Pending means not yet reviewed as executed.

The active next execution-method batch is [R08](workers/08-mips-emulation.md).
It starts with Ghidra 12.2's existing standalone P-code engine, original
synthetic MIPS instructions and declared callback models. It must compare
fields and callback order, intercept callbacks before body execution,
exercise delay slots, and reject deliberate offset/order errors. No
retail function or BIOS is part of its initial trial.

The [pinned MIPS semantics](https://github.com/NationalSecurityAgency/ghidra/blob/Ghidra_12.2_build/Ghidra/Processors/MIPS/data/languages/mips32Instructions.sinc)
assign load results directly to registers, while branch and call rules use
an explicit delay slot. This source review suggests that functional P-code
execution will not establish R3000 load-delay timing. R08 must record that
limit and check its actual stepping and return-address behavior.

A separate ready implementation batch is [R07](workers/07-sdk-provenance-export.md):
retain source-label provenance in a small companion to the current scanner,
with differential synthetic tests and equivalent-output checks against
R03's independently reproduced baseline. It leaves names and matcher
behavior unchanged. Its controlled timing check uses equal source scope;
the earlier differently scoped audit timings cannot establish a speedup.

Record negative results. A slower method can still reduce type repair.
A successful setup can still fail to distinguish compilers. Neither is
evidence that the roadmap's scene or gameplay milestones are complete.
