// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80064758.hpp"

namespace am3d::exe {

std::uint32_t call_80064758(std::uint32_t halfword, std::uint32_t mask) {
    const std::uint32_t bits = halfword & mask;
    // gap: lhu at t0+4 is unstated. beq at 0x80064764 is not followed.
    return bits;
}

}
