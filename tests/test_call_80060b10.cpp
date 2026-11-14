// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80060b10.hpp"

#include <cstdint>

using namespace am3d::exe;

int main() {
    std::uint32_t a0 = 0x1000u;
    std::uint32_t a1 = 0;
    std::uint32_t a2 = 0;
    std::uint32_t a3 = 0;
    std::uint32_t s0 = 0x8009f510u;
    std::uint16_t slot[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    std::uint32_t word_14 = 1;
    std::uint32_t word_18 = 1;
    std::uint32_t word_1c = 1;
    call_80060b10(a0, a1, a2, a3, s0, slot, word_14, word_18, word_1c);
    if (s0 != 0x800dd2d8u || a0 != 0x1000u || a1 != 0x1000u || a2 != 0xa00u ||
        a3 != 0x1000u) {
        return 1;
    }
    const std::uint16_t expect[9] = {0x1000u, 0, 0, 0, 0xa00u, 0, 0, 0, 0x1000u};
    for (int i = 0; i < 9; ++i) {
        if (slot[i] != expect[i]) return 2;
    }
    if (word_14 != 0 || word_18 != 0 || word_1c != 0) return 3;
    return 0;
}
