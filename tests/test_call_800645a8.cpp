// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800645a8.hpp"

#include <array>
#include <cstdint>

int main() {
    std::array<std::uint8_t, 248u> slots{};
    slots.fill(0xffu);
    const std::size_t off = 124u;
    am3d::exe::call_800645a8(1u, slots.data(), am3d::exe::kCall800645a8SlotStride);
    if (slots[0] != 0xffu) {
        return 1;
    }
    for (std::size_t i = 0; i < 0x15u; ++i) {
        if (slots[off + i] != 0u) {
            return 2;
        }
    }
    am3d::exe::call_800645a8(1u);
    return 0;
}