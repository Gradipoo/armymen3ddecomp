# Call at 0x8007eafc

`call-8007f920-12.md` returns here. `v0` is `0x800d6a14`. `s0` is `0x800d6a10`. `s1` is 0. `s2` is `0x18`. `sp` is `0x80010b24`.

`addiu` leaves `s1` as 4. `a0` becomes `0x800d6a14`. `a1` becomes 0. `jal` at `0x8007eb08` targets `0x8007f920`. The delay sets `a2` to `0x18`. `ra` leaves as `0x8007eb10`. `python3 tools/sdk_match.py` does not name `0x8007f920`. The earlier notes at that address stay. This note does not enter that body.

The frame at `0x8007eac8` stays open. Its saved `ra` stays `0x80045540`. The frame at `0x80045374` stays open. Its saved `ra` stays `0x800255e4`. The frame at `0x800251f8` stays open. Its saved `ra` stays `0x8007faec`.

## Our code

`am3d::exe::call_8007eafc` records the call target `0x8007f920`.

## Gap

The next note is `call-8007f920-13.md`. `a0` is `0x800d6a14`. `a1` is 0. `a2` is `0x18`. `ra` is `0x8007eb10`.
