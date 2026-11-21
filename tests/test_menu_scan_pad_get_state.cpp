// SPDX-License-Identifier: GPL-3.0-or-later
#include "menu_pad_get_state.hpp"

#include <cstdint>

int main() {
    constexpr std::uint16_t kReleased = 0xffffu;
    if (am3d::platform::menu_scan_pad_get_state(0u, kReleased) != 2u) {
        return 1;
    }
    if (am3d::platform::menu_scan_pad_get_state(0x12u, kReleased) != 2u) {
        return 2;
    }
    const std::uint16_t down =
        static_cast<std::uint16_t>(~(1u << am3d::platform::kPadBitDpadDown));
    if (am3d::platform::menu_scan_pad_get_state(0u, down) != 3u) {
        return 3;
    }
    const std::uint16_t up =
        static_cast<std::uint16_t>(~(1u << am3d::platform::kPadBitDpadUp));
    if (am3d::platform::menu_scan_pad_get_state(0u, up) != 1u) {
        return 4;
    }
    const std::uint16_t down_and_up = static_cast<std::uint16_t>(
        ~(1u << am3d::platform::kPadBitDpadDown) & ~(1u << am3d::platform::kPadBitDpadUp));
    if (am3d::platform::menu_scan_pad_get_state(0u, down_and_up) != 3u) {
        return 5;
    }
    return 0;
}