# R01 result: Shared type context

Date: November 13, 2026. Outcome: Passed for the synthetic trial.
Host: macOS 27.2.1 ARM64. Reviewed by the research coordinator on the same date.
This does not establish a retail improvement or verify a game function.

## Tools and inputs

The installed m2c package reports version 0.1.0. Its recorded source is
[`c632946b8cfbe8fce442b522dba92dfa72f1f317`](https://github.com/matt-kempster/m2c/tree/c632946b8cfbe8fce442b522dba92dfa72f1f317).
The reviewed [license is GPL version 3](https://github.com/matt-kempster/m2c/blob/c632946b8cfbe8fce442b522dba92dfa72f1f317/LICENSE).
Python was 3.12.16. The host compile check used Apple clang 21.0.0.
No upstream code was copied into public source files. No retail or SDK
input was read. The fixture and context are original synthetic inputs.

The fixture loads two signed halfwords at offsets 0 and 2 through its
argument, adds them and returns. It includes the load delay and a nop
return delay slot. The correct context declares two signed-short fields
and a pointer argument. A negative control declares signed-int fields.
All three use the same assembly input and `mipsel-gcc-c` target.

The pinned [m2c README](https://github.com/matt-kempster/m2c/blob/c632946b8cfbe8fce442b522dba92dfa72f1f317/README.md)
documents preprocessed context, target selection and optional caching.
The installed help was checked. This trial uses `--no-cache` throughout.
It tests the local context pattern used by
[SOTN's context helper](https://github.com/Xeeynamo/sotn-decomp/blob/b2350ec342ea498d0b838fdd19b6ed2dddc2595a/tools/m2ctx.py).
It does not reuse that project's preprocessing flags, game types, upload
path or source injection.

## Actual checks

| Check | No context | Correct context | Wrong-width context |
| --- | --- | --- | --- |
| m2c exit code | 0 | 0 | 0 |
| Diagnostics on stderr | None | None | None |
| Argument type | `void *` | `struct Pair *` | `struct Pair *` |
| Distinct unresolved field names | 2 | 0 | 2 |
| Struct declarations emitted | 0 | 0 | 0 |
| Explicit casts emitted | 0 | 0 | 0 |
| Manual draft edits under the rule below | 3 | 0 | Not scored |

Every draft returns `s32`. There are no called functions, so recovery of
callee prototypes was not tested. The untyped draft does not declare its
field widths or signs. The correct context supplies signed 16-bit fields.
Its draft uses both supplied members. This includes a parameter type
change as well as field names. It is useful type integration, not evidence
that m2c discovered an unknown structure.

For the manual-edit count, assume the same shared `Pair` declaration is
available to both drafts. Count one parameter-type replacement and one
replacement for each member identifier. The untyped draft needs three
replacements. The typed draft needs none. This is an edit count, not
measured work time. Writing and proving the context is excluded, so it
cannot support a claim about total labor saved.

The typed draft compiled with `-std=c11 -Wall -Wextra -Werror`. Five static
assertions checked short and int widths, struct size, and member offsets.
It passed 121 signed-value cases using eleven values per field, including
both signed-halfword extremes. Expected sums were prepared separately.
This is a synthetic host check. No MIPS emulator or byte-match check ran.

The wrong-width control still exited zero with no diagnostic. It retained
the supplied pointer type and emitted unresolved accesses at both offsets.
This output is a warning sign that needs review. A parse success cannot
confirm a supplied prototype or structure.

## Timing

Five fresh command processes ran for each mode after its initial run.
These warm runs used the same input and options. Each mode's output hash
was stable across its five runs.

| Mode | Median | Minimum | Maximum |
| --- | --- | --- | --- |
| No context | 84.43 ms | 84.05 ms | 89.55 ms |
| Correct context | 91.79 ms | 91.01 ms | 93.14 ms |

This trial shows no speed gain. Context parsing added about 7.36 ms to
the median on this tiny case. Process startup is included. Cached context,
larger corpora, other hosts and human review time were not measured.

## Context proposal

Keep declarations and their evidence separate. Each field record needs:

| Field | Meaning |
| --- | --- |
| Type and member | The declared structure and field name |
| Offset and width | Explicit byte counts under the target ABI |
| Signedness | Signed, unsigned, or unresolved |
| Evidence address | A supporting retail address, or null for synthetic input |
| Evidence kind | Instruction observation, caller use, or external API reference |
| Confidence | Proposed, reviewed, or unresolved |
| Source revision | The note revision or pinned upstream source |

Record function arguments and returns with the same evidence fields.
Only reviewed records should enter shared retail context. A type inferred
from a draft must remain proposed until checked against independent
evidence. Do not infer pointer width or long width from host headers.
No retail context or public header was added in this task.

## Reproduction and limits

The local directory is `build/research/context/`. It contains `fixture.s`,
`context.h`, `wrong-context.h`, the runner, captured outputs, the host check,
`manifest.json`, `validation.json`, and the success marker. The manifest
keeps exact argument lists, host and tool versions, tool and input hashes,
exit codes, elapsed times and artifact hashes. Generated C stays there.

```
build/analysis/venv/bin/python build/research/context/run_trial.py
build/analysis/venv/bin/m2c --target mipsel-gcc-c --no-cache build/research/context/fixture.s
build/analysis/venv/bin/m2c --target mipsel-gcc-c --no-cache --context build/research/context/context.h build/research/context/fixture.s
build/analysis/venv/bin/m2c --target mipsel-gcc-c --no-cache --context build/research/context/wrong-context.h build/research/context/fixture.s
python3 -m unittest discover -s tests -p test_prepare_function.py
python3 tools/pr_guard.py
```

Four preparation tests passed. The guard passed. There were zero failed
attempts. The wrong-width control was an expected successful process with
unresolved output, not a rejected input. The fixture was rerun once to add
the host layout and signed-value checks. The table uses that final run.

The coordinator checked every recorded input and artifact hash, reran all
three m2c modes and reproduced their output hashes, recomputed all 121
expected sums and the timing medians, and rebuilt and ran the host check.
All checks passed. The review record stays under the local `review/` folder.

Use reviewed context for the next separately assigned game gap. Treat
unresolved accesses as review items. Measure a larger local corpus before
claiming a speed or total-effort improvement. Do not change game names,
ledger status or verification based on this trial.
