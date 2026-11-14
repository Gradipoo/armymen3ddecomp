// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800752e8.hpp"
namespace am3d::exe {
std::uint32_t call_800752e8(std::uint32_t result, std::uint32_t s0) {
    if (result == 0) {
        return s0;
    }
    // gap: v0 is 0 on the traced other side, so this side is not taken.
    return result;
}
}
