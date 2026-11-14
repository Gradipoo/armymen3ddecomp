// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80070fb0.hpp"

#include <cstdint>

int main() {
    std::uint32_t words[19];
    for (int i = 0; i < 19; ++i) {
        words[i] = 1;
    }
    am3d::exe::call_80070fb0(words);
    if (words[2] != 0x200u || words[7] != 0x200u || words[12] != 0x200u || words[18] != 0) {
        return 1;
    }
    return 0;
}
