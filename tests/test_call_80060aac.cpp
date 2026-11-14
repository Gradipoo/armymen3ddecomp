// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80060aac.hpp"

#include <cstdint>
#include <cstdlib>
#include <iostream>

int main() {
    std::uint32_t a0 = 0x800d0000u;
    std::uint32_t cleared_word = 0xffffffffu;
    std::uint16_t first[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    std::uint16_t second_4 = 1;
    std::uint16_t second_a = 1;
    std::uint16_t second_10 = 1;
    am3d::exe::call_80060aac(a0, cleared_word, first, second_4, second_a, second_10);
    if (a0 != 0x1000u || cleared_word != 0 || second_4 != 0 || second_a != 0 ||
        second_10 != 0) {
        std::cerr << "call_80060aac registers changed\n";
        return EXIT_FAILURE;
    }
    const std::uint16_t expect[9] = {0, 0, 0x1000u, 0, 0, 0xf000u, 0, 0, 0};
    for (int i = 0; i < 9; ++i) {
        if (first[i] != expect[i]) {
            std::cerr << "call_80060aac halfword changed\n";
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}
