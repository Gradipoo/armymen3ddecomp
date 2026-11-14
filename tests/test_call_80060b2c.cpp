// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80060b2c.hpp"

#include <cstdint>

using namespace am3d::exe;

int main() {
    std::uint32_t a0 = 0x800dd2d8u;
    std::uint32_t word_14 = 1;
    std::uint32_t word_18 = 1;
    std::uint32_t stored = 1;
    std::uint32_t s0 = 0x800dd2d8u;
    const std::uint32_t ra = call_80060b2c(a0, word_14, word_18, stored, s0);
    if (a0 != 0x1000u || word_14 != 0 || word_18 != 0 || stored != 0x1000u) return 1;
    if (s0 != 0x8009f510u || ra != 0x80025478u) return 2;
    return 0;
}
