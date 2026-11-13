# R08: Synthetic MIPS differential execution

Status: Pending. No worker has executed this assignment.

## Question and scope

Can the installed Ghidra P-code engine execute an original MIPS fixture,
intercept known callbacks before their bodies execute, and compare fields
and callback order with our independent source model? This is a method
trial beyond host-only tests. No retail function, SDK body, BIOS, disc
image, asset or saved game state is an input.

Permitted public files: `tools/ghidra/scripts/ResearchMipsEmulation.java`,
`tools/research_emulation.py`, `tests/test_research_emulation.py`, and
`docs/workers/results/mips-emulation.md`.
Permitted local directory: `build/research/emulation/`.
No existing game source, Ghidra project, notes, inventory or ledger edits.
Read `docs/WORKERS.md`. Do not invoke cc1 or a stopped corpus helper.

## Existing engine and sources

Use installed Ghidra 12.2 rather than implementing a CPU. Its bundled
`StandAloneEmuExampleScript.java` shows a blank `PcodeEmulator`, shared
memory, register initialization and stepping without loading a program.
The [pinned upstream example](https://github.com/NationalSecurityAgency/ghidra/blob/Ghidra_12.2_build/Ghidra/Features/SystemEmulation/ghidra_scripts/StandAloneEmuExampleScript.java)
and [PcodeThread interface](https://github.com/NationalSecurityAgency/ghidra/blob/Ghidra_12.2_build/Ghidra/Framework/Emulation/src/main/java/ghidra/pcode/emu/PcodeThread.java)
are the primary references. The older EmulatorHelper API is not the
current bundled example. Check installed APIs before writing the adapter.
Review Apache-2.0 notices before adapting any upstream code.

Use `MIPS:LE:32:default` in a new emulator with synthetic memory only.
Do not call `EmulatorUtilities.loadProgram` on the retail project. If
headless startup needs an imported program, create a new temporary project
from a tiny original synthetic input under the task directory, disable
analysis, and never open the owner's project. Use isolated Ghidra settings,
cache, logs and temporary directories as in the reviewed R02 command.

## Synthetic cases and controls

Write a small original function with a stack frame, field stores, a
conditional branch, two fixed callback targets and a return. Include useful
work in at least one call delay slot. Establish an independent source model
with explicit 32-bit arithmetic and a byte-oriented state layout.
Assemble with the installed LLVM tool or encode reviewed original words.
Keep assembly and objects local. No old compiler is needed.

Define a strict allowed instruction range and a step cap. Before each
step, inspect the PC. Intercept a callback target before decoding or
executing its body, record a0-a3, its return address and the call order,
apply a declared synthetic return value, then resume at ra. Reject unknown
targets. A callback's memory must contain a trap or remain unmapped, so
accidental execution fails. A controlled final return target ends the run.

Ghidra instruction stepping can execute a branch and its delay slot as one
group. Confirm that behavior in this MIPS trial. Check that a callback
observes the delay slot's updated argument and returns to call address + 8.
Do not override the PC into the middle of an in-flight instruction group.

Run two input modes, including a zero-work or boundary case. Compare
defined output fields, callback order/arguments, return state and declared
clobbers. Initialize memory with at least two sentinel patterns. Define
which bytes are unspecified, which must be preserved, and which must be
written; never discard a difference just to make the results agree.

Negative controls must alter one field offset and one callback order.
Both must fail the comparison. A trap control must demonstrate that a
missed callback interception fails before any callee body can run.

## Commands and acceptance

```
python3 tools/research_emulation.py --help
python3 -m unittest discover -s tests -p test_research_emulation.py -v
python3 tools/pr_guard.py
```

Record the actual Ghidra and assembler invocation lists after implementing
the adapter. Default public checks use original synthetic data and fake
external-process handling only. Keep a real-engine integration check
optional when Ghidra is available. Require structured local evidence with
input/tool hashes, initial registers, memory ranges, callback events,
field comparisons, step count, exit reason and exact failure diagnostics.
Clear stale success output before a run. Reject report paths outside
`build/` and refuse to overwrite inputs or tools.

Acceptance requires correct output in both input modes and sentinel
patterns, deterministic repeats, callback-before-body interception, MIPS
delay-slot evidence, negative-control failures and a bounded unknown-PC
failure. Do not call a game function verified. Report the P-code model's
limits for real R3000 load delays, uninitialized state, devices, timing,
interrupts, callback assumptions and undefined C behavior.

Stop after three failed attempts at the same problem. Keep separate
problem counts for source setup, API compilation and execution semantics.
Do not combine unrelated resolved setup failures into a global stop.
