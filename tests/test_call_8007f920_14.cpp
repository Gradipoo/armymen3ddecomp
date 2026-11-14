// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007f920_14.hpp"

#include <cstdint>

int main() {
    std::uint8_t dest[12];
    for (int i = 0; i < 12; ++i) dest[i] = 0x11;
    am3d::exe::call_8007f920_14(dest);
    for (int i = 0; i < 12; ++i) {
        if (dest[i] != 0x11) return 1;
    }
    return 0;
}
