// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007abf8.hpp"

namespace am3d::exe {

void call_8007abf8(std::uint32_t a1, std::uint32_t a2, std::uint32_t a3, std::uint16_t slot[9],
    std::uint32_t& word_14, std::uint32_t& word_18, std::uint32_t& word_1c) {
    slot[0] = static_cast<std::uint16_t>(a1);
    slot[1] = 0;
    slot[2] = 0;
    slot[3] = 0;
    slot[4] = static_cast<std::uint16_t>(a2);
    slot[5] = 0;
    slot[6] = 0;
    slot[7] = 0;
    slot[8] = static_cast<std::uint16_t>(a3);
    word_1c = 0;
    word_18 = 0;
    word_14 = 0;
}

}
