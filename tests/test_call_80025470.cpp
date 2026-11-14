// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80025470.hpp"

using namespace am3d::exe;

int main() {
    std::uint32_t a0 = 0x800d0000u;
    std::uint32_t cleared_word = 1;
    std::uint16_t first[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    std::uint16_t second_4 = 1;
    std::uint16_t second_a = 1;
    std::uint16_t second_10 = 1;
    call_80025470(a0, cleared_word, first, second_4, second_a, second_10);
    if (a0 != 0x800dd2d8u || cleared_word != 0 || second_4 != 0 || second_a != 0 ||
        second_10 != 0) {
        return 1;
    }
    const std::uint16_t expect[9] = {0, 0, 0x1000u, 0, 0, 0xf000u, 0, 0, 0};
    for (int i = 0; i < 9; ++i) {
        if (first[i] != expect[i]) return 2;
    }
    return 0;
}
