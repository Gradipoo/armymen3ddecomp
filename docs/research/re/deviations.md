# Deviations

These lanes differ from the PlayStation game on purpose. Each one will be a `// gap:` in our code.

## Keyboard

The USA disc has no keyboard control. A later input path will add a keyboard.

Status: not started.

## Server browser

The USA disc has no server browser. A later path will show a server list.

Status: not started.

## Mods

A local `mods/` directory will be searched before the disc.

Status: not started.

## Mission path loop

The traced boot at `0x800237d0` keeps `s4` at 1 and `s1` at 0, so it calls `0x80063b34` again and does not reach the epilogue at `0x80023828`. The word at `0x800e152c` stays 0 on every traced load. Stores of that word exist at `0x80074200`, `0x8007428c`, `0x80074380`, `0x800744ac`, `0x800745f0`, `0x80074d38`, `0x80074e4c`, and `0x800750d0`, and none is on this path. The next block may start at `0x80023828` as the exit address. That start does not mean this boot took the branch.

The `sp` from that start is untrusted. `0x80063b34` opens with `addiu sp, sp, -0x88`. The returns in `call-80063b78.md` and `call-80063b78-2.md` pop that frame with `addiu sp, sp, 0x88` at `0x80063ed4` and resume `0x800237d0`. `call-80063b34-3.md` opens a third frame of `0x88`. No note pops it. `call-80062434-4.md` is still inside that frame, and `call-80062434.md` opened its own frame by `0x40`. `call-80023828.md` reads `0x24(sp)` as the saved `ra` of `0x80023794`. That slot is the `0x80023794` slot only after the `0x88` pop. `0x80060aac` is a separate frame of `0x18`. `call-80060b3c.md` pops it and returns to `0x80025478`. It is not the `0x88` frame, and it does not return through `0x80063b34`.

Status: the exit address stays. Sean reopened the stack. [stack-ledger.md](stack-ledger.md) states `sp` at `0x8002390c` as `0x80010bfc` after the inner pops. The third `0x88` frame has not reached that pop.

## VAB path loop

The traced boot at `0x800453c0` keeps `s1` and `s3` at 0, so `beq` at `0x800453c4` is not taken and does not reach `0x80045418`. [armymen-vab-loop.md](armymen-vab-loop.md) records that. The words at `0x800e152c` and `0x800e196c` stay 0. The next block may start at `0x80045418` as the exit address. That start does not mean this boot took the branch.

The only branch to `0x80045418` is `beq v0, zero` at `0x800453c4`. The first compare has `s1` equal to `s3`, so it does not take that branch. The later compare is reached from `beq s2, zero` at `0x80045410`, so `s2` is 0 when the exit is taken. `beq s2, zero, 0x80045510` at `0x80045418` is then taken. The forward notes start there. They do not claim that the static boot took `beq` at `0x800453c4`.

[stack-ledger.md](stack-ledger.md) leaves `sp` at `0x80010b44` inside the open frame at `0x80045374`. Its saved `ra` stays `0x800255e4`. The frame at `0x800251f8` stays open. Its saved `ra` stays `0x8007faec`.

Status: Sean said go. The forward trace starts at `0x80045418`.
