// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80012f94.hpp"
namespace am3d::exe {
namespace {
void store32(std::uint8_t* object, unsigned offset, std::uint32_t value) {
    object[offset] = static_cast<std::uint8_t>(value);
    object[offset + 1] = static_cast<std::uint8_t>(value >> 8);
    object[offset + 2] = static_cast<std::uint8_t>(value >> 16);
    object[offset + 3] = static_cast<std::uint8_t>(value >> 24);
}
void store16(std::uint8_t* object, unsigned offset, std::uint16_t value) {
    object[offset] = static_cast<std::uint8_t>(value);
    object[offset + 1] = static_cast<std::uint8_t>(value >> 8);
}
}
void call_80012f94(std::uint8_t* object) {
    store32(object, 0xcc, 0);
    store16(object, 0x120, 0x21);
    store16(object, 0x122, 0x64);
    store16(object, 0x126, 0x3e8);
    store32(object, 0xdc, 0);
    store32(object, 0xe4, 0);
    object[0x110] = 0;
    store32(object, 0x108, 0);
    object[0x111] = 0;
    store32(object, 0xe0, 0);
    store16(object, 0x124, 0x1f4);
    store16(object, 0x128, 0x1f4);
    store32(object, 0x7c, 0x400);
    store32(object, 0x12c, 0);
    store32(object, 0x130, 0);
    // gap: jal 0x800793ec. a0 is the object plus 0xe8. a1 is 0x80073df8. a2 is 0x8009f408. a3 is 0.
}
}
