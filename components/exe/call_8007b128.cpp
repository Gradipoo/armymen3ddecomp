// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007b128.hpp"
namespace am3d::exe {
std::uint32_t call_8007b128(std::uint32_t& a, std::uint32_t& b, std::uint32_t& c, std::uint32_t a1, std::uint32_t a2, std::uint32_t a3) {
    a += a1;
    c += a3;
    b += a2;
    return b;
}
}
