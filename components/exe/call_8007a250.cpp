// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007a250.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-8007a250.md.
std::uint32_t call_8007a250(Call8007a250Block& block, std::uint32_t a1,
                            Call8007a250Load load_word) {
    if (a1 != 0) {
        block.word0 |= 2u;
        if (block.link == 0) {
            block.at1c = 0;
        } else {
            block.at1c = load_word(block.link + 4u);
        }
        a1 = 0;
    } else {
        block.at1c = block.link;
        block.word0 &= 0xfffffffdu;
        a1 = block.word4;
    }
    const std::uint32_t result = block.at1c;
    block.at18 = a1;
    block.at14 = result;
    return result;
}

}
