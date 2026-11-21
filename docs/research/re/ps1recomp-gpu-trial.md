# Isolated PS1Recomp GPU trial

## Outcome and acceptance

On November 17, 2026, test a licensed candidate for the flat polygons and
paletted semi-transparent quads seen in the menu-exit list. Use original
synthetic words through the actual GPU command parser. Accept only the
interfaces and sampled pixels that execute successfully. Adoption also
requires integration and visible checks.

The trial is partial. Three primitive pixel checks passed. Two fill
alignment checks failed. The runner exited one. The build exited zero.
This candidate is not adopted, and no game function status changes.

## Selected source and dependencies

The selected source is [PS1Recomp revision
49c4a5164149a0b0eeaf1299f7cffa56d5ee1df1](https://github.com/PS1Recomp/ps1-recomp/tree/49c4a5164149a0b0eeaf1299f7cffa56d5ee1df1).
The archive SHA-256 is
`966a33ac407b3a6204c486772ab1fd69f9a2d7448b9258233c60855e78bda609`.
The root license declares GPL-3.0-or-later. Selected implementation files
are `ps1Runtime/src/gpu/gpu.cpp` and `ps1Runtime/src/metrics.cpp`, with their
corresponding runtime headers. No SDK, generated game source, game assets,
OpenGL, or SDL component was selected.

The formatting dependency is [fmt revision
f99d53024782bf928b07839140862163f15ade5b](https://github.com/fmtlib/fmt/tree/f99d53024782bf928b07839140862163f15ade5b),
used in header-only mode under its MIT license. Its archive SHA-256 is
`a603fe18c349adc8a7f3dfca7e488fcfd39210773ed52efc52eda67bd6699122`.
License notices remain with the local source trees. The standard C++ library
and system `execinfo` are also dependencies. No public source import was
made. Preserve all selected notices before a later import.

The tested host is macOS arm64 with Apple clang 21.0.0. Linux and Windows
were not tested. The archive URLs pin revisions; no Git checkout identity
was verified.

## Executed evidence

The original runner submits fixed 32-bit words through `GPU::writeGP0`.
It does not cast retail packet links to host pointers. Its sampled pixels
passed for a flat triangle, flat quad, and 4-bit paletted semi-transparent
textured quad. Synthetic CPU-to-VRAM commands uploaded the texture and
palette. The blend test sampled mode zero with constant texture coordinates.
It does not establish all texture modes, edge rules, or blend behavior.

A fill rectangle at `(3, 50)` with size `(1, 1)` left both `(0, 50)` and
`(15, 50)` zero, where the existing fill reference requires red after
horizontal alignment and width rounding. Both assertions failed. The source
explicitly omits that alignment. No patch was made to conceal the failure.

This trial exercised the real GP0 parser, unlike the preceding direct
[PsyZ renderer trial](psyz-synthetic-trial.md). It did not test ordering-table
traversal, empty tags, VRAM copy, display pages, clipping, controller input,
visible output, retail replay, or reconstructed game updates. A successful
synthetic pixel is not evidence of retail agreement.

## Integration decision

The licensed primitive path is feasible for a later bounded integration.
It cannot replace the current fill sink unchanged. The current
`FillVram::write_pixel` strips bit 15, while this GPU owns separate 16-bit
VRAM. A shared storage boundary must preserve that bit for textured
semi-transparency and retain the existing fill behavior.

The next bounded outcome is a local adapter that retains our fill semantics
in the candidate's VRAM, with synthetic checks for alignment, rounding,
masking, wrap, and preservation of the three passing primitive samples.
Keep it local until that boundary passes. This is not authority to migrate
the window or adopt an entire runtime.

Commands, complete dependency scan, runner hashes, build output, and failed
assertions remain under `build/coordination/licensed-graphics/`. The existing
SDL2 baseline was unchanged and was not redundantly rerun. The repository
guard passed.

The later [shared VRAM fill adapter trial](gpu-fill-adapter-trial.md) passed
26 synthetic assertions through a bounded complete-command interface. It
remains local and does not establish adoption or menu command coverage.
