// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80071184.hpp"
namespace am3d::exe {
void call_80071184(std::uint32_t a0, std::uint16_t& a, std::uint16_t& b, std::uint16_t& c) {
    a = static_cast<std::uint16_t>(a0);
    a0 = (a0 >> 1) & 0x7f7fu;
    b = static_cast<std::uint16_t>(a0);
    a0 = (a0 >> 1) & 0x3f3fu;
    c = static_cast<std::uint16_t>(a0);
}
}
