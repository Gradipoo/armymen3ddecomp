// SPDX-License-Identifier: GPL-3.0-or-later
#include "pack_tagged_word.hpp"

namespace am3d::exe {

std::uint32_t pack_tagged_word(std::uint32_t first, std::uint32_t second,
                               std::uint32_t third, std::uint32_t fourth) {
    std::uint32_t word = ((first + 1u) << 21) & 0x00e00000u;
    word |= ((second + 1u) << 17) & 0x001e0000u;
    word |= ((third + 1u) << 11) & 0x0001f800u;
    word |= (fourth + 1u) & 0x000007ffu;
    return word | 0x5a000000u;
}

}
