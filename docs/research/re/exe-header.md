# EXE header

Traced fact from the USA PS-X EXE. Re-check on a disc you own with `python3 tools/exe_info.py build/disc/SLUS_004.91`. The executable stays in `build/`.

- address: `0x8007f9f8`
- pc: `0x8007f9f8`
- load: `0x80010000`
- size: `0x000b5800`

The first block at `0x8007f9f8` is in [entry.md](entry.md). The rest of the body is not traced.

The same command prints `gp` and `text_offset`. Those two fields check that the header is still this file. This note does not close the gap in `components/exe/load.cpp`.
