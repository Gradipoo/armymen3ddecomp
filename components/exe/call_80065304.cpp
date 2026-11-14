// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80065304.hpp"
namespace am3d::exe {
std::uint32_t call_80065304(std::uint32_t index, std::uint8_t a1, std::uint8_t a2, std::uint8_t* base) {
    std::uint8_t* slot = base + (index << 2);
    slot[8] = a2;
    slot[9] = a1;
    return 0x800dd708u;
}
}
