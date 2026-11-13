# Compiler comparison for 0x80076274

This records the third calibration attempt for the display-fill function.
The earlier block and first two attempts stay in
[call-80076274.md](call-80076274.md). No SDK body was entered again.

## Controlled comparison

The local candidate source and flags were unchanged from attempt two.
Only the compiler changed from GCC 2.7.2 PSX to GCC 2.8.1 PSX. Both compiler
assets came from old-gcc release 0.17. The second archive was checked against
its upstream SHA-256 digest before extraction. Both are local tools under
`build/toolchains/`. The versions and archive hashes are recorded in
[toolchains.json](../../toolchains.json).

The adapter stayed at the pinned maspsx commit in ASPSX 2.56 mode. The
assembler stayed at LLVM 23.1.5, MIPS I little-endian. Flags remained
`-O2 -G0 -mips1 -mcpu=3000 -msoft-float -mno-abicalls -fgnu-linker -quiet`.

The candidate's known calls were bound with assembly constants. `DrawSync`
receives zero and returns to `0x8007628c` in retail. `DrawPrim` receives the
packet pointer and returns to `0x800762fc` in retail. The experiment did not
change those bindings or enter either body. It did not rewrite or trim the
generated instructions to force agreement.

| Attempt | Change | Result |
| --- | --- | --- |
| 1 | Initial GCC 2.7.2 candidate with absolute symbolic globals | LLVM rejected memory macros in MIPS I mode. |
| 2 | Explicit state address, with known call bindings | Assembled without unresolved relocations. Candidate 168 bytes, reference 152 bytes. |
| 3 | Same source and flags, GCC 2.8.1 PSX | Assembled without unresolved relocations. Candidate 160 bytes, reference 152 bytes. |

The source hash was checked against attempt two's provenance before the
third result was recorded. The entire candidate section was retained.
The difference is not section padding: its return delay slot is the final
word of the 160-byte section. There is no exact match.

## What was learned

The previous epilogue and address-loading differences already appeared in
GCC output. They were not introduced solely by maspsx or LLVM.

GCC 2.8.1 emits a return with stack release in the delay slot, as retail
does. It also saves an extra register and uses a larger stack frame than
retail. That combination is evidence of different code generation, not
proof that either tested compiler built the game. The candidate's state
fields use word-sized declarations while the retail operations read
halfwords. Source layout and type choices remain unconfirmed. Compiler
flags may also affect the result.

Three attempts at this matching problem have now failed. Stop this
calibration problem under AGENTS.md. Do not run an unattended flag search
or change the reference to produce a passing result. A later investigation
should first establish source types and layout from independent evidence.

The local third-attempt folder contains the source provenance, original
and adapted assembly, resolved-symbol object, disassembly, and result
metadata. All stay under `build/calibration/attempt3/`. The result includes
hashes for the source, executable, final assembly, and final object.
No raw code or retail bytes are copied into this note.

The portable function remains implemented, not verified. Host tests do
not settle this compiler question. The boot handoff remains in AGENTS.md;
this experiment does not advance execution to another retail function.
