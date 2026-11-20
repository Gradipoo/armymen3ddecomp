// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80064dc8.hpp"

namespace am3d::exe {

MenuLoopBody64dc8 call_80064dc8(std::uint32_t s1, const std::uint8_t* byte_at_s1) {
    MenuLoopBody64dc8 result{};
    std::uint8_t loaded = 0u;
    if (byte_at_s1 != nullptr) {
        loaded = *byte_at_s1;
    }
    result.v0 = static_cast<std::uint32_t>(loaded);
    result.s1 = s1 + 1u;
    if (loaded != 0u) {
        result.branch_to_65194 = true;
        // gap: re-entry at 0x80065194 is not modeled.
    } else {
        result.entered_64dd8 = true;
    }
    return result;
}

} // namespace am3d::exe