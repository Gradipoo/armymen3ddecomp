# SDK

Hits from `python3 tools/sdk_match.py` on the local PS-X EXE.

`0x8007faf8` is `word_fill`.
`0x8007fb1c` is `byte_compare`.
`0x8008824c` is `gpu_store`.

`tools/sdk_names.txt` has 383 more names. Psy-Q versions 260, 300, 330, 340, 350, 370, 400, 410, 420, 430, 440, 450, 460, and 470 agreed on each address. The names come from the public signature list at https://github.com/lab313ru/psx_psyq_signatures. That checkout stays under `build/`. The signature bytes are not in this tree.

`loc_` and `text_` labels were dropped. They are internal offsets, not public function names. 206 addresses had more than one name and stay unnamed. A name can appear at more than one address. Those rows still agreed across versions.

These functions are named. A later note that calls one of them records the name, the arguments, and the return address. It does not disassemble the body again.

Unmatched bytes stay untraced.
