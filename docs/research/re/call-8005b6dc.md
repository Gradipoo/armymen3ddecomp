# Call at 0x8005b6dc

`call-80065954.md` reaches here. `a0` is `0x41`. `a1` is 0. `ra` is `0x8006596c`. `sp` is `0x80010be4`.

`addiu` subtracts `0x18` from `sp`. `sp` is `0x80010bcc`. The saved `ra` is `0x8006596c`. `v0` becomes `0x800d8458`. `sb` stores `0x41` at `0x800d8744`. `jal` at `0x8005b6f0` targets `strcpy`. The delay sets `a0` to `0x800d8745`. `a1` stays 0. `ra` is `0x8005b6f8`. This note does not enter `strcpy`. This note does not state `v0`.

`lw` restores `ra` to `0x8006596c`. `jr ra` returns to `0x8006596c`. The delay adds `0x18` to `sp`. `sp` is `0x80010be4`. This frame closes.

The frame at `0x80065894` stays open. Its saved `ra` stays `0x800255ec`. The frame at `0x800251f8` stays open. Its saved `ra` stays `0x8007faec`.

## Our code

`am3d::exe::call_8005b6dc` records the return address `0x8006596c`.

## Gap

The next note is `call-8006596c.md`. The byte at `0x800d8744` is `0x41`. `a0` is `0x800d8745`. `s0` is `0x800e0000`. `sp` is `0x80010be4`.
