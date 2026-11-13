// SPDX-License-Identifier: GPL-3.0-or-later
#include "fill_vram.hpp"
#include <stdexcept>

using namespace am3d;

int main() {
    platform::FillVram vram;
    exe::DisplayFillState rect{0, 0, 17, 511, 18, 513};
    exe::fill_display(0x0000ffu, rect, vram);
    if (vram.pixel(15, 511) != 0 || vram.pixel(16, 511) != 31 ||
        vram.pixel(31, 0) != 31 || vram.pixel(32, 0) != 0 ||
        vram.argb(16, 511) != 0xffff0000u) return 1;

    rect = {0, 0, 1008, 4, 1040, 5};
    exe::fill_display(0x00ff00u, rect, vram);
    if (vram.pixel(1023, 4) != 0x3e0 || vram.pixel(0, 4) != 0x3e0 ||
        vram.pixel(15, 4) != 0x3e0 || vram.pixel(16, 4) != 0) return 2;

    rect = {0, 0, 0, 10, 0, 11};
    exe::fill_display(0xffffffu, rect, vram);
    if (vram.pixel(0, 10) != 0) return 3;
    rect = {0, 0, 0, 10, 16, 522};
    exe::fill_display(0xffffffu, rect, vram);
    if (vram.pixel(0, 10) != 0) return 4;

    try {
        vram.draw_prim({3u << 24, 0x600000ffu, 0, 0});
        return 5;
    } catch (const std::invalid_argument&) {}
    try {
        vram.draw_sync(1);
        return 6;
    } catch (const std::invalid_argument&) {}
    try {
        vram.pixel(1024, 0);
        return 7;
    } catch (const std::out_of_range&) {}
    return 0;
}
