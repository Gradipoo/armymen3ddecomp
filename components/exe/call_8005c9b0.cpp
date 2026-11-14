// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8005c9b0.hpp"
namespace am3d::exe {
std::uint32_t call_8005c9b0(const std::uint8_t* source, std::uint8_t* dest) {
    std::uint32_t index = 0;
    while (source[index] != 0 && source[index] != 0x3bu) {
        dest[index] = source[index];
        index += 1;
    }
    dest[index] = 0;
    return index;
}
}
