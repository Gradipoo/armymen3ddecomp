// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800278b8.hpp"
#include <cstdint>
#include <cstring>
namespace am3d::exe {
void call_800278b8(std::uint8_t* object) {
    const std::uint32_t pointer = 0x800bffd0u;
    std::memcpy(object + 0x44, &pointer, 4);
}
}
