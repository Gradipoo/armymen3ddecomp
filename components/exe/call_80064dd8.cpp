// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80064dd8.hpp"

namespace am3d::exe {

MenuLoopBody64dd8 call_80064dd8(std::uint32_t s1, const std::uint8_t* byte_at_s1) {
    (void)s1;
    MenuLoopBody64dd8 result{};
    std::uint8_t loaded = 0u;
    if (byte_at_s1 != nullptr) {
        loaded = *byte_at_s1;
    }
    result.v1 = 0x80u;
    result.v0 = static_cast<std::uint32_t>(loaded) & 0xf0u;
    result.t1 = 1u;
    if (result.v0 != result.v1) {
        result.branch_to_64dfc = true;
    } else {
        result.entered_64dec = true;
        // gap: body at 0x80064dec is not entered.
    }
    return result;
}

} // namespace am3d::exe