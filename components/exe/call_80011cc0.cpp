// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80011cc0.hpp"
namespace am3d::exe {
std::uint32_t call_80011cc0(std::uint8_t* base) {
    const std::uint32_t value = base[0x20] | 4u;
    base[0x21] = 0;
    base[0x20] = static_cast<std::uint8_t>(value);
    return value;
}
}
