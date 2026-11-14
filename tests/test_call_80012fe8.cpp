// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80012fe8.hpp"
#include <cstdint>
int main() {
    std::uint8_t object[0xa0] = {};
    if (am3d::exe::call_80012fe8(object) != object) return 1;
    auto* words = reinterpret_cast<std::uint32_t*>(object + 0x80);
    if (words[0] != 0u || words[1] != 0u) return 1;
    if (words[2] != 0x80073df8u || words[3] != 0x8009f408u) return 1;
    if (words[4] != 0u || words[5] != 0u) return 1;
    if (words[6] != 0xffffffffu || words[7] != 0u) return 1;
    return 0;
}
