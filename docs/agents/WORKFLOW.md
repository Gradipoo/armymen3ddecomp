# Agent workflow

Use this for shared work and handoffs. [AGENTS.md](../../AGENTS.md) holds
the project rules. [PLAN.md](../PLAN.md) sets priorities, and
[PROTOTYPE.md](../PROTOTYPE.md) defines prototype trials and acceptance.
The research method queue has its own contract in
[WORKERS.md](../WORKERS.md). This page does not widen a task's scope or
permission to publish.

## Team and ownership

For substantial work with an independent outcome, use one principal and
one autonomous worker by default. Use one agent when the work is small,
closely coupled, or needs the same game instance, browser, or files.
Add a specialist only when it removes a block or supplies a distinct check.
Do not build chains of supervisors who repeat the same investigation.

The principal owns the objective, key tradeoffs, integration, and acceptance.
The worker owns a substantial bounded result from investigation to delivery.
Give the worker authority for ordinary investigation and reversible fixes
within the assigned scope. Do not require permission for each command.
Existing publication and retail-data rules still apply.

Assign disjoint files and local output directories before work starts.
Use one operator per shared game, emulator, browser session, or capture.
Serialize dependent work. Do not run competing edits or game captures and
hope to separate them afterward. One gap per implementation change still
applies when several agents contribute.

## Delegation brief

Each assignment states:

- Outcome: the concrete result and what acceptance looks like.
- Inputs: relevant files, reproduction steps, and current facts with evidence.
- Ownership: files, local output directory, and shared resources reserved.
- Authority: permitted investigation and reversible changes within scope.
- Verification: required checks and the evidence to retain.
- Escalation: missing permission, a consequential design choice, a resource
  conflict, or evidence that invalidates the task.
- Delivery: result, changed files, decisive evidence, limits, and next action.

For a game gap, include its cited caller or entry and note limits. For a
prototype task, identify the screen dependency it removes. For a backend
trial, distinguish source review, synthetic checks, retail checks, and
adoption. Do not assign a broad hardware rewrite when one interface is the
next unresolved dependency.

## Communication and current state

Send internal messages when a decision or intervention is needed, a
dependency changes, a meaningful risk appears, or work is ready to integrate.
Do not send bare acknowledgments or command-by-command heartbeats.
Keep the user informed of meaningful progress under the session's rules.

Keep a short local state note under the task's `build/` directory. Record
accepted decisions, verified facts with evidence paths, open questions,
active ownership, and the next outcome. Mark abandoned hypotheses. Include
the current commit so facts can be checked after other work lands.

Use the roadmap, function ledger, research notes, and worker queue for
lasting public facts. Do not create a second completion ledger in a work
note. Retail contents, captures, generated code, and detailed logs stay
local. A handoff links to evidence instead of copying it into messages.

Give a specialist the relevant question and evidence. For independent
review, include the inputs, acceptance criteria, and decisive observations,
not only the implementer's conclusion. Keep useful history; start fresh
only when stale assumptions interfere with the work.

Search narrowly and bound tool output. Return summaries and artifact paths.
Keep raw logs in the task's local output directory and fetch detail when
needed. Do not send the same large logs to several agents.

## Waiting and reasoning

When no useful independent work remains, use a supported, permitted,
interruptible wait. Follow runtime limits. Prefer completion events and
bounded progress or log files to repeated short polls. Do not use blind
sleeps, keepalives, or model turns as a stopwatch. Verify timing claims
from actual tool call and return timestamps.

Use high reasoning effort for substantive debugging and implementation
when available. Lower effort suits clear mechanical tasks. Raise effort
for uncertainty or demonstrated failure. Use a stronger model for a
specific unresolved decision when permitted, not as a standing supervisor.
Judge the accepted outcome and required supervision, not token count alone.

## Acceptance and integration

Inspect decisive evidence and integrate the result. Do not repeat the
worker's whole investigation after each update. Run required checks and
resolve specific remaining doubts. Before extra validation, state the
question it answers and what either result changes. Do not skip mandatory
checks or a real environment observation needed to support the claim.

Preserve failures as evidence. Fix recurring environment problems at their
source when within scope. Three failures at the same problem stop the
attempt under AGENTS.md, including failures across agents or model changes.
Retire only the task's own superseded, reproducible outputs. Keep required
logs and do not delete another worker's artifacts or research notes.

If measuring workflow cost, compare similar accepted work blocks. Include
review time, retries, regressions, and the principal's and workers' usage.
Separate new input, cached input, and output. Do not double-count reasoning,
cumulative counters, or forked history. Label derived credit figures as
estimated equivalent credits, not invoices. Cached input still has a cost.
Measure one normal work block before changing several workflow choices.
Workflow research should remove repeated work on the current roadmap.
