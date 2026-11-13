// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8002fe4c.hpp"

#include <array>
#include <cstdint>

namespace {

void store_s32(std::uint8_t* dest, std::int32_t value) {
    const auto word = static_cast<std::uint32_t>(value);
    dest[0] = static_cast<std::uint8_t>(word);
    dest[1] = static_cast<std::uint8_t>(word >> 8);
    dest[2] = static_cast<std::uint8_t>(word >> 16);
    dest[3] = static_cast<std::uint8_t>(word >> 24);
}

}

int main() {
    std::array<std::uint8_t, am3d::exe::kCall8002fe4cBytes> object{};
    object.fill(0x11);
    object[0x35] = 0;
    store_s32(object.data() + 0x38, 10);
    store_s32(object.data() + 0x3c, 3);
    store_s32(object.data() + 0x44, 4);
    store_s32(object.data() + 0x48, 9);
    store_s32(object.data() + 0x50, 7);
    store_s32(object.data() + 0x54, 1);
    store_s32(object.data() + 0x5c, 20);
    store_s32(object.data() + 0x60, 8);
    const auto first = am3d::exe::call_8002fe4c(object.data(), 0x22u);
    if (first.negative_byte || first.low != 4 || first.high != 20 || first.pair_low != 3 ||
        first.bound != 1 || !first.bound_replaced || !first.delay_less) {
        return 1;
    }
    if (object[0x35] != 0 || object[0] != 0x11) return 2;

    store_s32(object.data() + 0x38, -5);
    store_s32(object.data() + 0x44, -8);
    store_s32(object.data() + 0x50, 2);
    store_s32(object.data() + 0x5c, -3);
    store_s32(object.data() + 0x3c, -1);
    store_s32(object.data() + 0x48, -4);
    store_s32(object.data() + 0x54, 9);
    store_s32(object.data() + 0x60, 9);
    const auto second = am3d::exe::call_8002fe4c(object.data(), 0x33u);
    if (second.low != -8 || second.high != 2 || second.pair_low != -4 || second.bound != 9 ||
        second.bound_replaced || !second.delay_less) {
        return 3;
    }

    object[0x35] = 0xff;
    const auto skipped = am3d::exe::call_8002fe4c(object.data(), 0);
    if (!skipped.negative_byte || skipped.low != 0) return 4;
    return 0;
}
