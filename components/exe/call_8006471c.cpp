// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8006471c.hpp"

namespace am3d::exe {

std::uint32_t call_8006471c(std::uint32_t index, std::uint32_t bits, std::uint32_t& masked) {
    const std::uint32_t record = 0x800dd748u + index * 124u;
    masked = bits & 0xffffu;
    // gap: lhu at record+0x1c is unstated. Taken side 0x800647c4 is not followed.
    // Static fallthrough is call_80064758. This function does not call it.
    return record;
}

}
