// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80057e78.hpp"
#include <cstring>
namespace am3d::exe {
std::uint8_t* call_80057e78(std::uint8_t* record, std::uint32_t value) {
    const std::uint32_t slot = 0x800c3554u;
    std::memcpy(record + 0x1c, &slot, 4);
    std::memcpy(record + 8, &value, 4);
    std::memset(record + 0x10, 0, 8);
    std::memset(record, 0, 2);
    std::memset(record + 2, 0, 2);
    std::memset(record + 4, 0, 2);
    std::memset(record + 0xc, 0, 2);
    return record;
}
}
