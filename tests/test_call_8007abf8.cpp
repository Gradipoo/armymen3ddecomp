// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007abf8.hpp"

#include <cstdint>

using namespace am3d::exe;

int main() {
    std::uint16_t slot[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    std::uint32_t word_14 = 1;
    std::uint32_t word_18 = 1;
    std::uint32_t word_1c = 1;
    call_8007abf8(0x1000u, 0xa00u, 0x1000u, slot, word_14, word_18, word_1c);
    const std::uint16_t expect[9] = {0x1000u, 0, 0, 0, 0xa00u, 0, 0, 0, 0x1000u};
    for (int i = 0; i < 9; ++i) {
        if (slot[i] != expect[i]) return 1;
    }
    if (word_14 != 0 || word_18 != 0 || word_1c != 0) return 2;
    return 0;
}
