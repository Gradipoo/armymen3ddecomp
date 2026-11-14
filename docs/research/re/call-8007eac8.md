# Call at 0x8007eac8

`call-8004552c.md` reaches here. `a0` is `0x800d6a10`. `a1` is 0. `a2` is `0x18`. `ra` is `0x80045540`. `sp` is `0x80010b44`.

`addiu` subtracts `0x20` from `sp`. `sp` becomes `0x80010b24`. The prologue saves `s0`, `s1`, `s2`, and `ra`. `s0` becomes `0x800d6a10`. `s1` becomes 0. `s2` becomes `0x18`. `a0` becomes `0x800d6a14`. `a1` becomes `0x80`. `a2` becomes `0x18`. The saved `ra` is `0x80045540`.

`jal` at `0x8007eaf4` targets `0x8007f920`. The delay stores 0 at `0x800d6a10`. `ra` leaves as `0x8007eafc`. `python3 tools/sdk_match.py` does not name `0x8007f920`. The earlier notes at that address stay. This note does not enter that body.

The frame at `0x8007eac8` stays open. Its saved `ra` is `0x80045540`. The frame at `0x80045374` stays open. Its saved `ra` stays `0x800255e4`. The frame at `0x800251f8` stays open. Its saved `ra` stays `0x8007faec`.

## Our code

`am3d::exe::call_8007eac8` records the call target `0x8007f920`.

## Gap

The next note is `call-8007f920-12.md`. `a0` is `0x800d6a14`. `a1` is `0x80`. `a2` is `0x18`. `ra` is `0x8007eafc`. The word at `0x800d6a10` is 0.
