// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8006508c.hpp"

namespace am3d::exe {

MenuS6Branch call_8006508c(std::uint32_t s6) {
    MenuS6Branch result{};
    result.v0 = 5u;
    result.s6_nonzero = s6 != 0u;
    // gap: bne at 0x8006508c is not followed.
    return result;
}

}
