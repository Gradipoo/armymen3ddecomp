// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80036258.hpp"
#include <cstdint>
#include <cstring>
int main() {
    std::uint8_t object[0x80] = {};
    if (am3d::exe::call_80036258(object, 1u, 2u, 3u) != 3u) return 1;
    std::uint32_t word = 0;
    std::memcpy(&word, object + 0x34 + 0x8, 4);
    if (word != 3u) return 1;
    std::memcpy(&word, object + 0x34 + 0x3c, 4);
    if (word != 1u) return 1;
    std::memcpy(&word, object + 0x34 + 0x44, 4);
    if (word != 3u) return 1;
    return 0;
}
