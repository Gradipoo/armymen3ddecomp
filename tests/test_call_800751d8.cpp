// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800751d8.hpp"

int main() {
    std::uint32_t stack_word = 0x80010b10u;
    std::uint32_t saved_word = 9;
    if (am3d::exe::call_800751d8(0, 0, stack_word, saved_word) != 1) return 1;
    if (stack_word != 0 || saved_word != 0) return 2;
    stack_word = 0x80010b10u;
    if (am3d::exe::call_800751d8(4, 0, stack_word, saved_word) != 1) return 3;
    if (stack_word != 0x80010b10u) return 4;
    return 0;
}
