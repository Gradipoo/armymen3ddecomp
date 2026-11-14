# Call at 0x8005be3c

[call-80074270.md](call-80074270.md) calls here. `a0` is 0. `ra` is `0x80074278`. This boot does not reach this address.

`v1` becomes `0x800d89b8`. `lw` at `0x8005be44` loads `0x800d89c4`. That address is inside the zero fill in [entry-after-fill.md](entry-after-fill.md). No traced note stores it, so `v0` is 0. `jr ra` returns to `0x80074278`. The delay stores 0 at `0x800d89c4`.

The 20 bytes from `0x8005be3c` through `0x8005be4c` occur once.

## Our code

`call_8005be3c` returns the old word and stores `a0`. The host check starts from 0.

## Gap

The next note resumes the caller at `0x80074278`. `v0` is 0.
