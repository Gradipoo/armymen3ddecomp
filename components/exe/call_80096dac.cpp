// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80096dac.hpp"
namespace am3d::exe {
std::uint32_t call_80096dac(std::uint32_t& word, std::uint8_t& low, std::uint8_t& high) {
    high = 0x4b;
    word = 0;
    low = 0;
    return 0x4bu;
}
}
