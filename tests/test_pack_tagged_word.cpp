// SPDX-License-Identifier: GPL-3.0-or-later
#include "pack_tagged_word.hpp"

using am3d::exe::pack_tagged_word;

int main() {
    if (pack_tagged_word(0, 0, 0, 0) != 0x5a220801u) return 1;
    if (pack_tagged_word(0xffffffffu, 0xffffffffu, 0xffffffffu, 0xffffffffu) != 0x5a000000u) return 2;
    if (pack_tagged_word(1, 2, 3, 4) != 0x5a462005u) return 3;
    if (pack_tagged_word(7, 15, 63, 0x7ffu) != 0x5a000000u) return 4;
    if (pack_tagged_word(8, 0xffffffffu, 0xffffffffu, 0xffffffffu) != 0x5a200000u) return 5;
    if (pack_tagged_word(0xffffffffu, 0xffffffffu, 0xffffffffu, 0x800u) != 0x5a000001u) return 6;
    return 0;
}
