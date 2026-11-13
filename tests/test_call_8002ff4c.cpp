// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8002ff4c.hpp"

#include <array>
#include <cstdint>
#include <limits>

namespace {

void store_s32(std::uint8_t* dest, std::int32_t value) {
    const auto word = static_cast<std::uint32_t>(value);
    dest[0] = static_cast<std::uint8_t>(word);
    dest[1] = static_cast<std::uint8_t>(word >> 8);
    dest[2] = static_cast<std::uint8_t>(word >> 16);
    dest[3] = static_cast<std::uint8_t>(word >> 24);
}

std::array<std::uint8_t, am3d::exe::kCall8002ff4cBytes> make_object() {
    std::array<std::uint8_t, am3d::exe::kCall8002ff4cBytes> object{};
    object.fill(0x11);
    object[0x35] = 0;
    return object;
}

}

int main() {
    auto object = make_object();
    store_s32(object.data() + 0x38, 10);
    store_s32(object.data() + 0x3c, 3);
    store_s32(object.data() + 0x44, 4);
    store_s32(object.data() + 0x48, 9);
    store_s32(object.data() + 0x50, 7);
    store_s32(object.data() + 0x54, 1);
    store_s32(object.data() + 0x5c, 20);
    store_s32(object.data() + 0x60, 8);
    const auto before = object;
    const auto first = am3d::exe::call_8002ff4c(object.data());
    if (!first.entered || first.y_low != 1 || first.y_high != 9 || first.x_low_shift != 0 ||
        first.x_high_shift != 0 || first.y_low_shift != 0 || first.y_high_shift != 0 ||
        first.x_skipped || first.y_skipped || !first.called || first.call_a0 != 0x800a03a8u ||
        first.call_a1 != object.data() || first.call_ra != 0x80030030u || object != before) {
        return 1;
    }

    store_s32(object.data() + 0x38, 16484);
    store_s32(object.data() + 0x3c, 10000);
    store_s32(object.data() + 0x44, 20000);
    store_s32(object.data() + 0x48, 20000);
    store_s32(object.data() + 0x50, 30000);
    store_s32(object.data() + 0x54, 8192);
    store_s32(object.data() + 0x5c, 40960);
    store_s32(object.data() + 0x60, 24626);
    const auto scaled = am3d::exe::call_8002ff4c(object.data());
    if (scaled.y_low != 8192 || scaled.y_high != 24626 || scaled.x_low_shift != 2 ||
        scaled.x_high_shift != 5 || scaled.y_low_shift != 1 || scaled.y_high_shift != 3 ||
        !scaled.called || scaled.call_a0 != 0x800a0bc8u) {
        return 2;
    }

    store_s32(object.data() + 0x38, 0);
    store_s32(object.data() + 0x44, 0);
    store_s32(object.data() + 0x50, 0);
    store_s32(object.data() + 0x5c, 0x40000);
    store_s32(object.data() + 0x3c, 0x40000);
    store_s32(object.data() + 0x48, 0);
    store_s32(object.data() + 0x54, 0);
    store_s32(object.data() + 0x60, 1);
    const auto clamped = am3d::exe::call_8002ff4c(object.data());
    if (clamped.x_high_shift != 31 || clamped.y_high_shift != 31 || clamped.x_low_shift != 0 ||
        clamped.y_low_shift != 0 || !clamped.called || clamped.call_a0 != 0x800a03a8u) {
        return 3;
    }

    store_s32(object.data() + 0x5c, 0x3ffff);
    store_s32(object.data() + 0x3c, 0x3ffff);
    const auto at_limit = am3d::exe::call_8002ff4c(object.data());
    if (at_limit.x_high_shift != 31 || at_limit.y_high_shift != 31 || !at_limit.called) {
        return 4;
    }

    store_s32(object.data() + 0x38, -100);
    store_s32(object.data() + 0x44, -50);
    store_s32(object.data() + 0x50, -20);
    store_s32(object.data() + 0x5c, -10);
    store_s32(object.data() + 0x3c, 4);
    store_s32(object.data() + 0x48, 6);
    store_s32(object.data() + 0x54, 1);
    store_s32(object.data() + 0x60, 3);
    const auto negative_x = am3d::exe::call_8002ff4c(object.data());
    if (!negative_x.x_skipped || negative_x.called || negative_x.x_low_shift != 0 ||
        negative_x.x_high_shift != -1 || negative_x.y_low != 1 || negative_x.y_high != 6) {
        return 5;
    }

    store_s32(object.data() + 0x38, 0);
    store_s32(object.data() + 0x44, 0);
    store_s32(object.data() + 0x50, 0);
    store_s32(object.data() + 0x5c, 100);
    store_s32(object.data() + 0x3c, -80);
    store_s32(object.data() + 0x48, -40);
    store_s32(object.data() + 0x54, -100);
    store_s32(object.data() + 0x60, -5);
    const auto negative_y = am3d::exe::call_8002ff4c(object.data());
    if (negative_y.x_skipped || !negative_y.y_skipped || negative_y.called ||
        negative_y.y_low_shift != 0 || negative_y.y_high_shift != -1) {
        return 6;
    }

    store_s32(object.data() + 0x54, 9);
    store_s32(object.data() + 0x60, 9);
    const auto other = am3d::exe::call_8002ff4c(object.data());
    if (other.entered || other.called) return 7;

    const auto most_negative = std::numeric_limits<std::int32_t>::min();
    store_s32(object.data() + 0x38, most_negative);
    store_s32(object.data() + 0x44, most_negative);
    store_s32(object.data() + 0x50, most_negative);
    store_s32(object.data() + 0x5c, most_negative);
    store_s32(object.data() + 0x54, 1);
    store_s32(object.data() + 0x60, 2);
    const auto wide = am3d::exe::call_8002ff4c(object.data());
    if (!wide.x_skipped || wide.x_high_shift != -262144 || wide.called) return 8;
    return 0;
}
