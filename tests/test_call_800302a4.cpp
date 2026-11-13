// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800302a4.hpp"

#include <array>
#include <cstdint>

int main() {
    std::array<std::uint8_t, am3d::exe::kCall800302a4Bytes> object{};
    object.fill(0x11);
    object[am3d::exe::kCall800302a4ByteOffset] = 0;
    am3d::exe::call_800302a4(object.data(), 0x22u);
    for (std::size_t i = 0; i < object.size(); ++i) {
        std::uint8_t expect = 0x11;
        if (i == am3d::exe::kCall800302a4ByteOffset) expect = 0;
        if (object[i] != expect) return 1;
    }

    object[am3d::exe::kCall800302a4ByteOffset] = 1;
    am3d::exe::call_800302a4(object.data(), 0x33u);
    if (object[am3d::exe::kCall800302a4ByteOffset] != 1) return 2;
    return 0;
}
