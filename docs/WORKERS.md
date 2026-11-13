# Research worker queue

These are local method trials. A task file is an assignment, not evidence
that it ran. Every task starts Pending. A coordinator changes its status
after reviewing the result and the retained local evidence.

Read [AGENTS.md](../AGENTS.md), [RESEARCH.md](RESEARCH.md), and the task.
Do not edit the roadmap, another worker's files, existing block notes,
the function inventory, SDK names, or the progress ledger in these trials.
Actual game changes still close one gap per change.

| Order | Task | Status | Dependency |
| --- | --- | --- | --- |
| 1 | [Shared context](workers/01-shared-context.md) | Passed synthetic trial, reviewed | [Result](workers/results/shared-context.md) |
| 2 | [Boundaries and duplicate leads](workers/02-boundaries-duplicates.md) | Passed filter and metadata trial, reviewed | [Result](workers/results/boundaries-duplicates.md); whole routines unresolved |
| 3 | [SDK provenance](workers/03-sdk-provenance.md) | Passed provenance trial, reviewed | [Result](workers/results/sdk-provenance.md); no new names |
| 4 | [Mismatch viewer](workers/04-mismatch-viewer.md) | Passed objdiff synthetic trial, reviewed | [Result](workers/results/mismatch-viewer.md); asm-differ/LLVM path blocked |
| 5 | [Compiler corpus](workers/05-compiler-corpus.md) | Failed setup trial, stopped and reviewed | [Result](workers/results/compiler-corpus.md); no compiler conclusions |
| 6 | [Behavior evidence](workers/06-behavior-evidence.md) | Discovery/proposal reviewed; capture prerequisites open | [Result](workers/results/behavior-evidence.md); zero captures |
| 7 | [SDK provenance export](workers/07-sdk-provenance-export.md) | Pending | Reviewed R03 baseline; isolated tooling change |
| 8 | [Synthetic MIPS execution](workers/08-mips-emulation.md) | Pending | Installed Ghidra P-code engine; no retail input |

Tasks 1, 3, 4 and 5 can start independently with synthetic inputs.
Task 2 must not publish new game function claims without a separate gap
assignment. Task 6 first specifies and tests evidence collection. It does
not certify a game function by running host tests.

## Shared contract

The coordinator assigns one task and the worker claims only its listed
files. Each task has its own `build/research/TASK/` directory. Other
workers must not replace those files. Run commands from the repo root.
Tool paths shown for this Mac are examples. Record the actual paths and
host. Use Python 3 for our tools. Keep optional dependencies isolated.

The only public result is a short fact report in the task's permitted
`docs/workers/results/` file, plus any explicitly permitted synthetic
fixtures or our tools. Reports cite upstream URLs and address facts.
Keep executable bytes, local hashes and file paths, generated C, assembly,
objects, traces, screenshots, and detailed diff reports under `build/`.
Do not post to decomp.me or use a distributed permuter. Do not fetch a
proprietary SDK. Do not send a GitHub issue, PR, or push.

Record exact commands as JSON argument lists and tool versions, revisions,
licenses, SHA-256 values, source inputs, exit codes, elapsed times, and
artifact locations in a local `manifest.json`. Record both successes and
failures. Before a run, remove that task's previous success marker so a
failed run cannot look current. Do not remove another worker's outputs.

Stop after three failed attempts at the same problem. Preserve the logs.
Report what changed, what was learned, and what remains uncertain. The
stopped 0x80076274 matching experiment and PsyCross build cannot be
reopened by these tasks, even with another tool, flags, or worker.

## Result format

Each public result gives:

1. Task ID, date, host and actual outcome: Passed, Failed, or Blocked.
2. Tool revisions and license sources. State whether any code was copied.
3. The acceptance checks that actually ran, with counts and scope.
4. Measured baseline and candidate results. Use "not measured" where needed.
5. Failure count, open limits, and a recommendation supported by the data.
6. Commands needed to repeat the synthetic checks. List local artifact
   names without including retail contents or owner-specific paths.

Run the task's checks and `python3 tools/pr_guard.py`. A method can pass
its synthetic trial without being adopted or improving retail results.
No task automatically changes names, implementation status, or verification.
