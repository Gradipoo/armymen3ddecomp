// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800268e4.hpp"
#include <cstdint>
#include <cstring>
namespace am3d::exe {
void call_800268e4(std::uint8_t* object) {
    const std::uint32_t pointer = 0x800bff68u;
    std::memcpy(object + 0x24, &pointer, 4);
}
}
