// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80096d6c.hpp"
#include <cstdint>
#include <cstring>
int main() {
    std::uint8_t object[0x38] = {};
    if (am3d::exe::call_80096d6c(object, 0x11) != 1u) return 1;
    if (object[0x37] != 0x46 || object[0x24] != 0x11 || object[0x36] != 1) return 1;
    std::uint32_t pointer = 0;
    std::memcpy(&pointer, object + 0x2c, 4);
    if (pointer != static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(object + 0x24))) return 1;
    return 0;
}
