// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80062434.hpp"

int main() {
    std::uint8_t dest[9] = {};
    std::uint32_t a0 = 0;
    am3d::exe::call_80062434(dest, a0, 0x8009f444u);
    if (a0 != 0x8009f444u) return 1;
    if (dest[0] != 0x6c || dest[1] != 0x65 || dest[2] != 0x67 || dest[3] != 0x61) return 1;
    if (dest[4] != 0x6c || dest[5] != 0x2e || dest[6] != 0x62 || dest[7] != 0x67) return 1;
    if (dest[8] != 0) return 1;
    return 0;
}
