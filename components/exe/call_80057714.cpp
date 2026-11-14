// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80057714.hpp"
#include <cstdint>
#include <cstring>
namespace am3d::exe {
namespace {
void half(std::uint8_t* base, unsigned offset, std::uint16_t value) {
    std::memcpy(base + offset, &value, 2);
}
void word(std::uint8_t* base, unsigned offset) {
    const std::uint32_t zero = 0;
    std::memcpy(base + offset, &zero, 4);
}
void header(std::uint8_t* v1, std::uint8_t* a3) {
    word(a3, 0x34);
    word(a3, 0x14);
    half(v1, 0x64, 0);
    half(v1, 0x62, 0);
    half(v1, 0x60, 0);
    word(v1, 0x68);
    half(v1, 0x6c, 0);
    half(v1, 0x72, 0x1000);
    half(v1, 0x70, 0x1000);
    half(v1, 0x6e, 0x1000);
}
}
void call_80057714(std::uint8_t* base) {
    header(base, base);
    for (unsigned offset = 0; offset < 6; offset += 2) {
        half(base, offset, 0);
        half(base, offset + 0x20, 0);
    }
    header(base + 0x18, base + 4);
    half(base, 6, 0);
    half(base, 0x26, 0);
}
}
