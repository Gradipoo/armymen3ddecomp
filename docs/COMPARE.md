# Local code comparison

`tools/compare.py` checks a candidate code range against the local executable.
It uses Python's standard library. It does not download or install tools.

For a candidate ELF32 little-endian MIPS object or executable:

```
python tools/compare.py build/disc/SLUS_004.91 build/candidate.o --address ADDRESS --size SIZE
```

Replace ADDRESS and SIZE with the confirmed virtual address and byte count.
Both must be word-aligned. Numbers accept decimal or a `0x` prefix.
Use `--section NAME` for a section other than `.text`.
Use `--format raw` for a file containing only candidate machine code.

The candidate section must have exactly the requested byte count. The tool
does not trim padding, move instructions, mask bits, or apply relocations.
A section with relocation records must be linked before comparison. Check
that its placement and referenced addresses match the reference layout.
An object section may contain several functions. Isolate the intended range
before using it for a single-function check.

Exit codes:

| Code | Result |
| --- | --- |
| 0 | Every compared byte matches. |
| 1 | The ranges differ. |
| 2 | The input cannot be compared. |

Each completed comparison writes a JSON report under `build/compare/`.
It includes the range, input hashes, and differences by instruction word.
Reports contain retail bytes. They stay local. A later completed comparison
of the same address replaces the report. Input errors do not replace it.
Always check the exit code and hashes when using a report.

The reference size must come from reviewed boundaries. Ghidra's inventory
size counts body addresses and may include several separate ranges. It is
not proof that the same number of bytes from the entry is one function.

The local compile-and-compare loop now passes our synthetic unsigned-add
fixture. See [TOOLCHAIN.md](TOOLCHAIN.md). The original compiler and assembler
have not been calibrated against retail code. No match of our game code has
been established yet. A modern host build cannot serve as a PS1 machine-code
candidate.

For each function, record compiler version, flags, link layout, address,
size, hashes, and the result in a public verification note. Keep the actual
report under `build/`. Copying the reference into a candidate is not a
verification of reconstructed source. An exact match of a partial range
does not verify a whole function. This tool never advances the progress
ledger automatically.

The next stage is to calibrate an original-era compiler and assembler on
small functions. Until then, use these checks to inspect already available
MIPS candidates and use synthetic inputs to test the comparison tool.
