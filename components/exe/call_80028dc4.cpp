// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80028dc4.hpp"
namespace am3d::exe {
std::uint32_t call_80028dc4(std::uint32_t value, std::uint32_t& word) {
    word = value;
    return 0x800d0000u;
}
}
