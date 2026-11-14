// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80096d4c.hpp"
#include <cstdint>
#include <cstring>
namespace am3d::exe {
std::uint32_t call_80096d4c(std::uint8_t* object, std::uint8_t value) {
    object[0x37] = 0x4c;
    const auto pointer = static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(object + 0x24));
    std::memcpy(object + 0x2c, &pointer, 4);
    object[0x24] = value;
    object[0x36] = 1;
    return 1u;
}
}
