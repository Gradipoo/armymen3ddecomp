// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80036258.hpp"
#include <cstring>
namespace am3d::exe {
std::uint32_t call_80036258(std::uint8_t* object, std::uint32_t second, std::uint32_t third, std::uint32_t fourth) {
    std::uint8_t* base = object + 0x34;
    std::memcpy(base + 0x3c, &second, 4);
    std::memcpy(base + 0x40, &third, 4);
    std::memcpy(base + 0x44, &fourth, 4);
    const std::uint32_t three = 3u;
    std::memcpy(base + 0x8, &three, 4);
    return 3u;
}
}
