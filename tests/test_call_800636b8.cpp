// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800636b8.hpp"

int main() {
    std::uint8_t dest[6] = {};
    std::uint32_t length = 0;
    am3d::exe::call_800636b8(dest, length);
    if (length != 5) return 1;
    if (dest[0] != 0x64 || dest[1] != 0x61 || dest[2] != 0x74) return 1;
    if (dest[3] != 0x61 || dest[4] != 0x5c || dest[5] != 0) return 1;
    return 0;
}
