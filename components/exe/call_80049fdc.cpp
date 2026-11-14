// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80049fdc.hpp"
namespace am3d::exe {
std::uint32_t call_80049fdc(std::uint32_t* base) {
    std::uint32_t* source = base + (0xb8 / 4);
    std::uint32_t* dest = base + (0x18 / 4);
    for (int left = 2; left != -1; left -= 1) {
        *dest = *source;
        source += 1;
        dest += 1;
    }
    return 1;
}
}
