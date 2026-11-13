// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80010cc4.hpp"

#include <array>
#include <cstdint>

int main() {
    std::array<std::uint8_t, 4> object{};
    object.fill(0x11);
    am3d::exe::call_80010cc4(object.data(), 0x22u);
    for (std::uint8_t byte : object) {
        if (byte != 0x11) return 1;
    }
    return 0;
}
