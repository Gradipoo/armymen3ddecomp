// SPDX-License-Identifier: GPL-3.0-or-later
#include "pack_stack_tagged_word.hpp"

using am3d::exe::pack_stack_tagged_word;

int main() {
    if (pack_stack_tagged_word(0, 0, 0, 0, 0) != 0x01220801u) return 1;
    if (pack_stack_tagged_word(0xffffffffu, 0xffffffffu, 0xffffffffu, 0xffffffffu, 0xffffffffu) != 0) {
        return 2;
    }
    if (pack_stack_tagged_word(1, 2, 3, 4, 5) != 0x06462005u) return 3;
    if (pack_stack_tagged_word(7, 15, 63, 0x7ffu, 0x7fu) != 0) return 4;
    if (pack_stack_tagged_word(8, 0xffffffffu, 0xffffffffu, 0xffffffffu, 0xffffffffu) != 0x00200000u) {
        return 5;
    }
    if (pack_stack_tagged_word(0xffffffffu, 0xffffffffu, 0xffffffffu, 0x800u, 0xffffffffu) != 1u) {
        return 6;
    }
    if (pack_stack_tagged_word(0xffffffffu, 0xffffffffu, 0xffffffffu, 0xffffffffu, 0x80u) != 0x01000000u) {
        return 7;
    }
    return 0;
}
