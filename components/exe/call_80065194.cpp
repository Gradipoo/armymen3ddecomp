// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80065194.hpp"

namespace am3d::exe {

MenuLoopFallthrough call_80065194(std::uint32_t s5) {
    MenuLoopFallthrough result{};
    if (s5 != 0u) {
        result.branch_to_651c8 = true;
        // gap: body at 0x800651c8 is not entered.
        return result;
    }
    result.entered_6519c = true;
    result.v0 = 0x800e0000u;
    return result;
}

} // namespace am3d::exe