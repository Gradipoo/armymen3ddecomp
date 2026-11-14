// SPDX-License-Identifier: GPL-3.0-or-later
#include "fill_vram.hpp"
#include <stdexcept>

namespace am3d::platform {

FillVram::FillVram() : pixels_(width * height, 0) {}

void FillVram::draw_sync(int mode) {
    if (mode != 0) {
        throw std::invalid_argument("unsupported DrawSync mode");
    }
    // This sink completes its supported command synchronously.
}

void FillVram::draw_prim(const exe::FillPacket& packet) {
    // The three-word fill is tag high byte 3 and command byte 2.
    // Display-area top byte 0x05 is built at 0x80086e48. x and y are not quoted.
    // The next cited GPU word is 0x08000002, from the jalr at 0x80086fcc.
    // This sink paints the fill. It does not paint that word.
    if ((packet[0] >> 24) != 3 || (packet[1] >> 24) != 2) {
        throw std::invalid_argument("unsupported GPU packet");
    }
    const unsigned x = packet[2] & 0x3f0;
    const unsigned y = (packet[2] >> 16) & 0x1ff;
    const unsigned w = ((packet[3] & 0x3ff) + 15) & ~15u;
    const unsigned h = (packet[3] >> 16) & 0x1ff;
    const auto color = static_cast<std::uint16_t>(
        ((packet[1] >> 3) & 0x001f) |
        ((packet[1] >> 6) & 0x03e0) |
        ((packet[1] >> 9) & 0x7c00));
    for (unsigned row = 0; row < h; ++row) {
        for (unsigned col = 0; col < w; ++col) {
            pixels_[((y + row) & 511) * width + ((x + col) & 1023)] = color;
        }
    }
}

void FillVram::write_pixel(unsigned x, unsigned y, std::uint16_t rgb555) {
    if (x >= width || y >= height) {
        throw std::out_of_range("VRAM coordinate out of range");
    }
    pixels_[y * width + x] = static_cast<std::uint16_t>(rgb555 & 0x7fff);
}

std::uint16_t FillVram::pixel(unsigned x, unsigned y) const {
    if (x >= width || y >= height) {
        throw std::out_of_range("VRAM coordinate out of range");
    }
    return pixels_[y * width + x];
}

std::uint32_t FillVram::argb(unsigned x, unsigned y) const {
    const auto color = pixel(x, y);
    const auto expand = [](unsigned value) { return (value << 3) | (value >> 2); };
    return 0xff000000u | (expand(color & 31) << 16) |
        (expand((color >> 5) & 31) << 8) | expand((color >> 10) & 31);
}

}
