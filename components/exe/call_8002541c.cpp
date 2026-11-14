// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8002541c.hpp"

#include "call_8002542c.hpp"
#include "call_80025470.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-8002541c.md.
// Copy the loaded word into v0. The delay slot replaces a0.
// entry-compare-result.md stores 0 at 0x8007f9a8, so this boot takes 0x80025470.
void call_8002541c(std::uint32_t& a0, std::uint32_t word, std::uint32_t& v0) {
    v0 = word;
    a0 = 0x800d0000u;
    if (v0 == 0) {
        std::uint32_t cleared_word = 0;
        std::uint16_t first[9] = {};
        std::uint16_t second_4 = 0;
        std::uint16_t second_a = 0;
        std::uint16_t second_10 = 0;
        call_80025470(a0, cleared_word, first, second_4, second_a, second_10);
        return;
    }
    call_8002542c(a0);
}

}
