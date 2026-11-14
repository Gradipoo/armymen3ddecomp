// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8005ca30.hpp"
#include "call_8005ca00.hpp"
namespace am3d::exe {
const std::uint8_t* call_8005ca30(const std::uint8_t* text) {
    if (toupper(text[1]) != 'D') {
        return text;
    }
    // gap: the second byte is not 0x44 for the cited strings.
    return text;
}
}
