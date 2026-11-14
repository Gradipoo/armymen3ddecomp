// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80060aac.hpp"

namespace am3d::exe {

void call_80060aac(std::uint32_t& a0, std::uint32_t& cleared_word, std::uint16_t first[9],
    std::uint16_t& second_4, std::uint16_t& second_a, std::uint16_t& second_10) {
    a0 = 0x1000u;
    cleared_word = 0;
    first[0] = 0;
    first[2] = 0x1000u;
    first[1] = 0;
    first[3] = 0;
    first[4] = 0;
    first[5] = 0xf000u;
    first[6] = 0;
    first[7] = 0;
    first[8] = 0;
    second_4 = 0;
    second_a = 0;
    second_10 = 0;
    // gap: unnamed call at 0x80060b58. a0 is 0x1000. The return address is 0x80060b10.
}

}
