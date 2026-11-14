# Bytes for the three compares

Traced fact from the USA PS-X EXE. The executable stays in `build/`. Re-check on a disc you own. The load address is `0x80010000`. The text starts at file offset `0x800`. The file offset of an address is `0x800` plus that address minus the load address.

These are the `a0` addresses already named for the three calls to `byte_compare`. The first is in [entry-after-ram.md](entry-after-ram.md). The second is in [entry-after-compare.md](entry-after-compare.md). The third is in [entry-after-second-compare.md](entry-after-second-compare.md). This note quotes the executable bytes. It does not quote the BIOS ROM. It does not state whether any compare matches. It does not state the word at `0x8007f9a8`.

At `0x8007f9d8`, file offset `0x701d8`, the 10 bytes are `44 54 4c 2d 48 32 30 30 30 00`. The first nine bytes are the characters `DTL-H2000`. The tenth byte is 0.

At `0x8007f9e2`, file offset `0x701e2`, the 10 bytes are `44 54 4c 2d 48 32 35 30 30 00`. The first nine bytes are the characters `DTL-H2500`. The tenth byte is 0.

At `0x8007f9ec`, file offset `0x701ec`, the 10 bytes are `44 54 4c 2d 48 32 37 30 30 00`. The first nine bytes are the characters `DTL-H2700`. The tenth byte is 0.

Each run ends at its first 0 byte. `0x8007f9d8` plus 10 is `0x8007f9e2`. `0x8007f9e2` plus 10 is `0x8007f9ec`. `0x8007f9ec` plus 10 is `0x8007f9f6`. The bytes at `0x8007f9f6` and `0x8007f9f7` are 0. The entry at `0x8007f9f8` is the next word. This note does not trace that entry again.

The traced fills do not cover these addresses. The scratchpad fill stays at `0x1f800000`. The zero fill in [entry-after-fill.md](entry-after-fill.md) starts at `0x800c5458`. The fill in [entry-after-zero.md](entry-after-zero.md) starts at `0x800e44e0`. These bytes sit inside the text image, `0x80010000` through `0x800c57ff`. This note does not close the gap in `components/exe/load.cpp`. It does not choose the `beq` at `0x80025424`.
