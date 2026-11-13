// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8001d434.hpp"

namespace am3d::exe {
namespace {

std::uint32_t sign_extended_byte(std::uint8_t byte) {
    const std::uint32_t widened = static_cast<std::uint32_t>(byte) << 24;
    const std::uint32_t low = widened >> 24;
    if ((widened & 0x80000000u) == 0) return low;
    return low | 0xffffff00u;
}

}

// Behavior reference: docs/research/re/call-8001d434.md.
void call_8001d434(std::uint8_t* text, Call8001d434Tolower tolower) {
    while (true) {
        const std::uint8_t byte = *text;
        if (byte == 0) return;
        // gap: tolower at 0x8007ff80. a0 is the sign-extended byte. The return address is 0x8001d450.
        const std::uint32_t result = tolower(sign_extended_byte(byte));
        *text = static_cast<std::uint8_t>(result);
        ++text;
    }
}

}
