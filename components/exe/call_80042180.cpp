// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80042180.hpp"
namespace am3d::exe {
void call_80042180(std::uint32_t x, std::uint32_t y, std::uint32_t z, std::uint16_t h, std::uint32_t w, std::uint32_t* out) {
    out[0] = x;
    out[1] = y;
    out[2] = z;
    out[3] = h;
    out[4] = w;
}
}
