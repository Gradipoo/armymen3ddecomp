// SPDX-License-Identifier: GPL-3.0-or-later
#include "front_tim.hpp"

using namespace am3d;

namespace {

void put16(std::uint8_t* at, unsigned value) {
    at[0] = static_cast<std::uint8_t>(value);
    at[1] = static_cast<std::uint8_t>(value >> 8);
}

void put32(std::uint8_t* at, unsigned value) {
    put16(at, value);
    put16(at + 2, value >> 16);
}

}

int main() {
    // Four pixels, two colors. The low nibble is the left pixel.
    // Color 0 is skipped. Color 1 is white.
    std::uint8_t bytes[8 + 16 + 14] = {};
    put32(bytes + 0, 0x10);
    put32(bytes + 4, 0x8);
    put32(bytes + 8, 16);
    put16(bytes + 12, 0);
    put16(bytes + 14, 0);
    put16(bytes + 16, 2);
    put16(bytes + 18, 1);
    put16(bytes + 20, 0);
    put16(bytes + 22, 0x7fff);
    put32(bytes + 24, 14);
    put16(bytes + 28, 0);
    put16(bytes + 30, 0);
    put16(bytes + 32, 1);
    put16(bytes + 34, 1);
    put16(bytes + 36, 0x0001);

    platform::FillVram vram;
    platform::FrontTim picture;
    if (!platform::paint_front_tim(bytes, sizeof bytes, 10, 20, vram, &picture)) return 1;
    if (picture.width != 4 || picture.height != 1) return 2;
    if (vram.pixel(10, 20) != 0x7fff) return 3;
    if (vram.pixel(11, 20) != 0 || vram.pixel(12, 20) != 0 || vram.pixel(13, 20) != 0) return 4;

    bytes[0] = 0;
    if (platform::paint_front_tim(bytes, sizeof bytes, 0, 0, vram, nullptr)) return 5;
    return 0;
}
