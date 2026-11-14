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
    std::uint16_t slot0 = 1;
    std::uint16_t slot6 = 1;
    std::uint16_t slot12 = 1;
    std::uint16_t slot2 = 1;
    std::uint16_t slot8 = 1;
    std::uint16_t slot14 = 1;
    std::uint32_t a1 = 0;
    std::uint32_t a2 = 0;
    std::uint32_t a3 = 0;
    std::uint32_t s0 = 0x8009f510u;
    am3d::exe::call_80060aac(a0, cleared_word, first, second_4, second_a, second_10, slot0,
        slot6, slot12, slot2, slot8, slot14, a1, a2, a3, s0);
    if (a0 != 0x800dd2d8u || s0 != 0x800dd2d8u || a1 != 0x1000u || a2 != 0xa00u ||
        a3 != 0x1000u || cleared_word != 0 || second_4 != 0 || second_a != 0 ||
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
    if (slot0 != 0x1000u || slot6 != 0x1000u || slot12 != 0x1000u || slot2 != 0x1000u ||
        slot8 != 0x1000u || slot14 != 0x1000u) {
        std::cerr << "call_80060aac callee halfword changed\n";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
