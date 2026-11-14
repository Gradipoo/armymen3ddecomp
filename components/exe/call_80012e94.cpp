// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80012e94.hpp"
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
void call_80012e94(std::uint8_t* object, std::uint32_t second, const std::uint8_t* table) {
    store32(object, 0x68, 0x800c005cu);
    call_8002fb9c(object, second, table);
    std::uint32_t at_6c = 1;
    std::uint16_t at_70 = 1, at_72 = 1;
    std::uint32_t at_74 = 1;
    call_80010c7c(at_6c, at_70, at_72, at_74);
    store32(object, 0x6c, at_6c);
    store16(object, 0x70, at_70);
    store16(object, 0x72, at_72);
    store32(object, 0x74, at_74);
    store32(object, 0x68, 0x800be980u);
    store16(object, 0x10c, 1);
    store32(object, 0x118, 4);
    store32(object, 0xa0, 0);
    static constexpr std::uint32_t first[] = {0x1000, 0, 0x1000, 0, 0x1000, 0, 0, 0};
    for (unsigned i = 0; i < 8; ++i) store32(object, 0xa4 + i * 4, first[i]);
    object[0x112] = 0;
    store32(object, 0xd0, 0);
    store32(object, 0xd4, 0);
    store32(object, 0xd8, 0);
    store32(object, 0xc4, 0);
    store32(object, 0xc8, 0);
    // gap: the next instruction is 0x80012f94.
}
}
