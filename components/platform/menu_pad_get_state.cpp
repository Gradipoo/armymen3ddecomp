// SPDX-License-Identifier: GPL-3.0-or-later
#include "menu_pad_get_state.hpp"

namespace am3d::platform {

namespace {

bool held(std::uint16_t buttons, unsigned bit) {
    return (buttons & (1u << bit)) == 0u;
}

}  // namespace

std::uint32_t menu_scan_pad_get_state(std::uint32_t port, std::uint16_t buttons) {
    (void)port;
    if (held(buttons, kPadBitDpadDown)) {
        return 3u;
    }
    if (held(buttons, kPadBitDpadUp)) {
        return 1u;
    }
    if (held(buttons, kPadBitDpadLeft)) {
        return 4u;
    }
    if (held(buttons, kPadBitDpadRight)) {
        return 5u;
    }
    if (held(buttons, kPadBitCross)) {
        return 6u;
    }
    return 2u;
}

}  // namespace am3d::platform