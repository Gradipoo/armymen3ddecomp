// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80018b64.hpp"
#include <cstring>
namespace am3d::exe {
std::uint32_t call_80018b64(std::uint8_t* object, std::uint32_t second, std::uint32_t third, std::uint32_t fourth) {
    std::memcpy(object + 0x30, &third, 4);
    std::memcpy(object + 0x34, &second, 4);
    std::memcpy(object + 0x38, &fourth, 4);
    const std::uint32_t three = 3u;
    std::memcpy(object + 0x8, &three, 4);
    return 3u;
}
}
