# SDK

Hits from `python3 tools/sdk_match.py` on the local PS-X EXE.

`0x8007faf8` is `word_fill`.
`0x8007fb1c` is `byte_compare`.
`0x8008824c` is `gpu_store`.

These three functions are named. A later note that calls one of them records the name, the arguments, and the return address. It does not disassemble the body again.

Unmatched bytes stay untraced.
