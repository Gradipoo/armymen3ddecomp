// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80030ba4.hpp"
namespace am3d::exe {
std::uint32_t call_80030ba4(std::uint32_t& x, std::uint32_t& y, std::uint32_t& z, std::uint32_t a1, std::uint32_t a2, std::uint32_t a3) {
    x += a1;
    z += a3;
    y += a2;
    return y;
}
}
