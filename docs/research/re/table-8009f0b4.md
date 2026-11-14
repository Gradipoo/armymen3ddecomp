# Words at 0x8009f0b4

The eight words sit in the text image, `0x80010000` through `0x800c57ff`. The zero fill in [entry-after-fill.md](entry-after-fill.md) starts at `0x800c5458`. No traced note stores these words.

`0x8009f0b4` is `0x00001000`. `0x8009f0b8` is 0. `0x8009f0bc` is `0x00001000`. `0x8009f0c0` is 0. `0x8009f0c4` is `0x00001000`. `0x8009f0c8` is 0. `0x8009f0cc` is 0. `0x8009f0d0` is 0.

[call-8002fb9c.md](call-8002fb9c.md) copies these eight words onto offsets `0x4` through `0x23`.

## Our code

`components/exe/table_8009f0b4.hpp` holds those 32 bytes. No ledger row is added.
