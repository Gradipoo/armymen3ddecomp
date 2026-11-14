// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80063668.hpp"

int main() {
    std::uint8_t dest[9] = {};
    std::uint32_t a1 = 1;
    am3d::exe::call_80063668(dest, a1, 0x8009f444u);
    if (a1 != 0x8009f444u) return 1;
    if (dest[0] != 0x6c || dest[8] != 0) return 1;
    return 0;
}
