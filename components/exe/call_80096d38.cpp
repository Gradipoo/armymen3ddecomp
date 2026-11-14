// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80096d38.hpp"
namespace am3d::exe {
std::uint32_t call_80096d38(std::uint32_t& word, std::uint8_t& low, std::uint8_t& high) {
    high = 0x45;
    word = 0;
    low = 0;
    return 0x45u;
}
}
