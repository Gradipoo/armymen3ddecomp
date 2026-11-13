# R02 result: Boundaries and duplicate leads

Date: November 13, 2026. Outcome: Passed for the synthetic filter and
metadata checks. Whole-routine and shared-behavior claims remain unresolved.
Host: macOS 27.2.1 ARM64, Python 3.15.2. Reviewed by the research coordinator
on the same date.

## Tools and scope

The trial used our standard-library duplicate filter and SDK name matcher.
Their exact file hashes and commands stay in the local manifest. Our tools
carry GPL-3.0-or-later notices. No upstream code was copied into public
files. The only public output from this worker is this report.

Ghidra 12.2 PUBLIC supplied saved function-body address ranges. Its build
date is October 23, 2026. Its root [license is Apache 2.0](https://github.com/NationalSecurityAgency/ghidra/blob/Ghidra_12.2_build/LICENSE).
The coordinator's metadata exporter was run against a copy of the existing
project with `-noanalysis -readOnly`. It did not import, analyze, disassemble,
or decompile the executable. All original and copied project file hashes
remained unchanged.

[SOTN's duplicate tool](https://github.com/Xeeynamo/sotn-decomp/blob/b2350ec342ea498d0b838fdd19b6ed2dddc2595a/tools/dups/src/main.rs)
uses the top six MIPS opcode bits as its comparison key and a similarity
threshold. That is a broader search for leads. This trial instead checked
equal bytes in provisional windows, without masking or instruction
decoding. Neither method establishes equal behavior by its score alone.
SOTN's tool was reviewed as a design reference, not installed or benchmarked.

## Actual checks

All eight existing synthetic unit tests passed. Ten independent checks
also passed: equal windows, a one-byte change, different window sizes,
nested overlaps, small and outside windows, an unaligned entry, a truncated
EXE, and three rejected path cases. The path cases used a test root inside
the worker directory, so even an unexpected write would stay local.

The altered same-size window did not group. Different-size windows did
not group together. Every nested-overlap participant was excluded. The
unaligned inventory and truncated EXE returned the expected error exit.
Outside-root paths, parent traversal and a symlink escape were rejected.
The public tests also checked failed-run report invalidation and refusal
to overwrite inputs.

The worker independently recomputed exclusions with pairwise interval
checks and grouped the remaining full byte windows. Every group and the
exclusion counts agreed with the production filter. The worker's JSON
report also matched the coordinator's earlier report exactly. Input hashes
agreed with the local files.

| Local inventory scan | Count |
| --- | --- |
| Inventory entries | 1,869 |
| Considered windows | 1,786 |
| Excluded entries | 83 |
| Below the 16-byte minimum | 81 |
| In overlapping windows | 2 |
| Equal-window groups | 20 |
| Entries in those groups | 82 |

No current exclusion was outside the EXE text. The synthetic checks covered
that case. These are window counts. They are not counts of implementations
saved, verified functions, or labor saved. Speed and review effort were
not measured.

## Saved body metadata

The export contains 1,869 functions. Every address, size and name agrees
with the existing TSV. Its imported-image hash matches the EXE text image,
which was imported without the PS-X header.
That hash identifies the original imported file. It does not establish
that every byte of the current Ghidra program memory is unchanged.

| Saved Ghidra body shape | Count |
| --- | --- |
| One address range | 1,862 |
| Two address ranges | 5 |
| Three address ranges | 2 |
| Not exactly one range starting at entry with the recorded size | 8 |

The last row includes seven multi-range bodies and one single-range body
whose range begins before its entry. None of these eight entries belongs
to the 20 equal-window groups. This finding confirms why a body address
count alone cannot supply a trusted contiguous comparison range.

The coordinator's new metadata validator passed all seven synthetic tests
and accepted 1,861 eligible metadata windows in the local export. It found
seven discontiguous bodies, no overlapping body address sets, and a
consistent inventory. Its results agreed with this worker's independent
shape check. Every member of the 20 duplicate groups was metadata eligible.
Eligibility remains a lead for later boundary review.

The first five groups, ordered by address, contain 26 members. No member
has a named SDK entry in the current matcher. Metadata checks give:

| Group | Members | Members with one contiguous saved range starting at entry | Whole-routine classification |
| --- | --- | --- | --- |
| 1 | 2 | 2 | Unresolved |
| 2 | 3 | 3 | Unresolved |
| 3 | 17 | 17 | Unresolved |
| 4 | 2 | 2 | Unresolved |
| 5 | 2 | 2 | Unresolved |

No branch targets, delay slots, callers, relative references or instruction
bodies were reviewed. The metadata is an existing automatic analysis
result, not independent evidence that each body is a complete routine.
It cannot distinguish a whole routine, a partial routine, or data with
confidence. The local group records preserve the addresses for a later
one-gap assignment. No SDK or BIOS body was entered.

## Runs, evidence and limits

The metadata exporter compiled and ran successfully on its first attempt.
That run took 4.066 seconds. Ghidra logged a nonfatal cache-maintenance write
refusal outside the task directory. Its valid export and logs are preserved.
A second run used explicit settings, cache, application temporary and Java
temporary directories inside the worker directory. It took 4.050 seconds
and produced identical export bytes. No cache error remained. An offline
OS truststore warning remained in the log. Neither run changed the source
or copied project.

A third export checked the coordinator's filename and input-protection
updates. It succeeded in 3.914 seconds and produced the same metadata
bytes. It retained the isolated settings and cache paths. The final
manifest records the updated exporter hash and all three invocations.

The coordinator independently checked all 78 recorded artifacts and both
project copies' file hashes, reran the current duplicate tool and reproduced
the exact report, recomputed the inventory and body-shape counts, and ran
another read-only Ghidra export with isolated caches. That export was
byte-identical and neither project changed. The coordinator's eight
metadata tests also passed, including nonzero conflict status and stale
report invalidation. The local `../review/` folder retains this review.

There were zero failed checks or failed exporter attempts. The cache
isolation issue was corrected once. Expected negative-control errors are
recorded separately from failures. The guard passed after the trial and
again after this public report was written.

All detailed evidence is under `build/research/duplicates/worker/`:

- `manifest.json` records exact commands, input hashes, exit codes and logs.
- `run_trial.py`, `synthetic/` and `validation.json` preserve the independent checks.
- `leads.json` is the independent local window report.
- `first-five-groups.json` and `boundary-summary.json` retain the review limits.
- `function-ranges.json` and `noncontiguous-metadata.json` retain address metadata.
- `metadata-command.json` and `run_metadata.py` record the Ghidra invocation.
- `ranges-check.json` records the metadata validator's result.
- `review_metadata.py` repeats the independent range and source checks.
- `original-project-hashes.json` records the unchanged source project.
- `first-metadata/` retains the first export and cache warning.
- `second-metadata/` retains the first fully isolated export.

Repeat the synthetic and scan checks from the repo root:

```
python3 build/research/duplicates/worker/run_trial.py
python3 build/research/duplicates/worker/review_metadata.py
python3 -m unittest discover -s tests -p test_research_duplicates.py -v
python3 tools/pr_guard.py
```

`run_metadata.py` records this host's installed launcher and Java paths.
It uses the existing copied project and the metadata-only exporter. Other
hosts need their own explicit paths. Both scripts and all game-derived
reports remain local.

Keep the filter as a conservative prioritization aid. Require saved ranges
and a separate instruction review before treating a candidate as one whole
function. Do not rename, merge implementations, or advance the ledger from
these groups. Consult the validator's saved-range evidence before local
function preparation. Document an intentional subrange when a note covers
a block rather than a whole routine. A separate instruction review is
required before accepting a whole-function boundary.
