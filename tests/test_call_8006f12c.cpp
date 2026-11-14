// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8006f12c.hpp"

#include <cstdint>

int main() {
    std::uint32_t words[19];
    for (int i = 0; i < 19; ++i) {
        words[i] = 1;
    }
    am3d::exe::call_8006f12c(words);
    if (words[2] != 0x200u || words[7] != 0x200u || words[12] != 0x200u) {
        return 1;
    }
    for (int i = 0; i < 19; ++i) {
        if (i == 2 || i == 7 || i == 12) {
            continue;
        }
        if (words[i] != 0) {
            return 1;
        }
    }
    return 0;
}
