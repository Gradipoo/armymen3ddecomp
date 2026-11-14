// SPDX-License-Identifier: GPL-3.0-or-later
#include "front_tim.hpp"

namespace am3d::platform {
namespace {

bool read_u16(const std::uint8_t* bytes, std::size_t size, std::size_t at, unsigned* out) {
    if (at + 2 > size) return false;
    *out = bytes[at] | (static_cast<unsigned>(bytes[at + 1]) << 8);
    return true;
}

bool read_u32(const std::uint8_t* bytes, std::size_t size, std::size_t at, unsigned* out) {
    if (at + 4 > size) return false;
    *out = bytes[at] | (static_cast<unsigned>(bytes[at + 1]) << 8) |
        (static_cast<unsigned>(bytes[at + 2]) << 16) |
        (static_cast<unsigned>(bytes[at + 3]) << 24);
    return true;
}

}

bool paint_front_tim(const std::uint8_t* bytes, std::size_t size,
    unsigned origin_x, unsigned origin_y, FillVram& vram, FrontTim* out) {
    unsigned magic = 0, flag = 0, clut_bytes = 0;
    if (!read_u32(bytes, size, 0, &magic) || magic != 0x10) return false;
    if (!read_u32(bytes, size, 4, &flag) || flag != 0x8) return false;
    if (!read_u32(bytes, size, 8, &clut_bytes) || clut_bytes < 12) return false;
    unsigned clut_x = 0, clut_y = 0, clut_w = 0, clut_h = 0;
    if (!read_u16(bytes, size, 12, &clut_x) || !read_u16(bytes, size, 14, &clut_y) ||
        !read_u16(bytes, size, 16, &clut_w) || !read_u16(bytes, size, 18, &clut_h)) {
        return false;
    }
    if (clut_x > 1023 || clut_y > 511) return false;
    if (clut_w == 0 || clut_h == 0) return false;
    const unsigned clut_colors = clut_w * clut_h;
    if (clut_bytes != 12u + clut_colors * 2u) return false;
    const std::size_t image_at = 8u + clut_bytes;
    unsigned image_bytes = 0, image_x = 0, image_y = 0, image_w = 0, image_h = 0;
    if (!read_u32(bytes, size, image_at, &image_bytes) || image_bytes < 12) return false;
    if (!read_u16(bytes, size, image_at + 4, &image_x) ||
        !read_u16(bytes, size, image_at + 6, &image_y) ||
        !read_u16(bytes, size, image_at + 8, &image_w) ||
        !read_u16(bytes, size, image_at + 10, &image_h)) {
        return false;
    }
    if (image_x > 1023 || image_y > 511) return false;
    if (image_w == 0 || image_h == 0) return false;
    if (image_bytes != 12u + image_w * 2u * image_h) return false;
    if (image_at + image_bytes != size) return false;
    const unsigned pixel_w = image_w * 4u;
    const std::size_t colors_at = 20;
    const std::size_t pixels_at = image_at + 12;
    for (unsigned row = 0; row < image_h; ++row) {
        for (unsigned word_i = 0; word_i < image_w; ++word_i) {
            unsigned packed = 0;
            if (!read_u16(bytes, size, pixels_at + (row * image_w + word_i) * 2u, &packed)) {
                return false;
            }
            for (unsigned nibble = 0; nibble < 4; ++nibble) {
                const unsigned index = (packed >> (nibble * 4)) & 0xf;
                if (index >= clut_colors) return false;
                unsigned color = 0;
                if (!read_u16(bytes, size, colors_at + index * 2u, &color)) return false;
                if (color == 0) continue;
                vram.write_pixel(origin_x + word_i * 4u + nibble, origin_y + row,
                    static_cast<std::uint16_t>(color & 0x7fff));
            }
        }
    }
    if (out) {
        out->width = pixel_w;
        out->height = image_h;
    }
    return true;
}

}
