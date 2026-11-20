// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80064f78.hpp"

namespace am3d::exe {

MenuCompareFourResult call_80064f78(std::uint32_t complemented_a0) {
    MenuCompareFourResult result{};
    constexpr std::uint32_t kMaskFff9 = 0xfff9u;
    result.masked_complement = complemented_a0 & kMaskFff9;
    result.branch_to_65168 = result.masked_complement == 0u;
    // Delay slot at 0x80064f80 always runs after the beq at 0x80064f7c.
    result.v0 = 1u;
    // gap: body at 0x80065168 when masked complement is zero.
    return result;
}

}