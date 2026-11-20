// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80065194.hpp"

namespace am3d::exe {

MenuLoopFallthrough call_80065194(std::uint32_t s5) {
    MenuLoopFallthrough result{};
    if (s5 != 0u) {
        result.branch_to_651c8 = true;
        result.v0 = 0x800e0000u;
        return result;
    }
    result.entered_6519c = true;
    result.v0 = 0x800e0000u;
    return result;
}

} // namespace am3d::exe