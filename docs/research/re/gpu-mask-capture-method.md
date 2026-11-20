# GPU mask capture method review

## Outcome and acceptance

On November 19, 2026, prepare a focused live GPU mask-state observation at
the menu's DrawOTag submission. Require a demonstrated live GPUSTAT read,
frame and caller evidence, and a bounded capture. Do not use a debugger
memory shadow as hardware state.

The proposed Lua memory read is unsuitable. Version-matched upstream source
shows it returns hardware shadow bytes rather than live GPUSTAT. No capture
hook was launched and no emulator run occurred. Retail mask state remains
unknown. The [retained-list restrictions](menu-list-contract.md) remain.

## Decisive source evidence

The source revision is `7637751dc246876ee658e94825d9c91129fef820`, matching
the installed bundle's reported changeset. That metadata is not independent
proof of binary provenance.

The [Lua binding](https://github.com/grumpycoders/pcsx-redux/blob/7637751dc246876ee658e94825d9c91129fef820/src/core/pcsxlua.cc#L294)
wraps `Memory::getMemoryAsFile`. Its
[file interface](https://github.com/grumpycoders/pcsx-redux/blob/7637751dc246876ee658e94825d9c91129fef820/src/lua/fileffi.lua#L119)
passes `readU32At` through the raw file-read path. The
[memory implementation](https://github.com/grumpycoders/pcsx-redux/blob/7637751dc246876ee658e94825d9c91129fef820/src/core/psxmem.cc#L850)
uses `readBlock`, obtains a debug pointer, and copies bytes. The
[debug mapping](https://github.com/grumpycoders/pcsx-redux/blob/7637751dc246876ee658e94825d9c91129fef820/src/core/psxmem.h#L334)
resolves page `0x1f80` to the hardware shadow. This path does not dispatch
a live GPU status read. Reading `0x1f801814` through it cannot establish
GPUSTAT bits 11 and 12.

The documented Lua GPU interface lists no direct status-read method. The
ordinary guest CPU hardware-read path is different from this debug File
path. Its ability to read live status does not make the Lua read equivalent.

## Limits and next observation

Even a valid sample at DrawOTag entry would precede the copy. Evidence must
also rule out an intervening E6 command, reset, or other relevant state
change before treating it as the copy's mask state. The retained packet
list alone does not establish state from earlier submissions.

The next bounded method is to identify an already executed guest GP1 status
load from permitted existing research and observe its result after the
load delay. Establish its relation to the target submission and intervening
state changes before claiming a measurement. Do not inject a guest load,
re-enter named SDK bodies, or guess a live register value. If that route
cannot be established, a separately verified live-status accessor is needed.

Selected upstream source, exact source links, source hashes, and the local
readiness record remain under `build/coordination/mask-capture/`. No game
files were fetched, no backend or adapter changed, and no runtime result is
claimed. The repository guard passed. This is a method rejection, not a
retail observation or game function completion.

## Existing guest-read review

The November 19 review found a startup poll in
[call-800883ec.md](call-800883ec.md) and
[call-80088458.md](call-80088458.md). The latter identifies `v1` as
`0x1f801814`, but its observed `v0` contains only bit 26 after masking.
Those notes do not identify an explicit full-word observation PC, load
destination and delay sequence, or a relation to the captured menu
submission. They are not sufficient to prepare the requested capture.

[call-800882c4.md](call-800882c4.md) and
[call-8008824c.md](call-8008824c.md) load a port pointer and then write
control words. Those pointer loads are not GPU status reads. No named SDK
body was entered again, and no executable was read for this review.

Searches, key input hashes, and the readiness result remain under
`build/coordination/guest-status-read/`. No script or emulator run occurred.
The repository guard passed. Mask state and the retained-list restrictions
remain unchanged. The next method needs a separately verified live GPU
status accessor rather than another shadow-memory read or an inferred
startup-to-menu relationship.

The later [local live-status accessor trial](live-gpu-status-accessor.md)
passed a no-disc software-GPU Lua-binding test and built a local app
executable. No retail mask capture or visible app launch has occurred.
