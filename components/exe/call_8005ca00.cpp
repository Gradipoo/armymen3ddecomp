// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8005ca00.hpp"
namespace am3d::exe {
std::uint32_t toupper(std::uint32_t byte) {
    if (byte == 'l') {
        return 'L';
    }
    return byte;
}
const std::uint8_t* call_8005ca00(const std::uint8_t* text) {
    if (toupper(text[0]) == 'C') {
        // gap: the compare with 0x43 is not taken for the cited strings.
    }
    return text;
}
}
