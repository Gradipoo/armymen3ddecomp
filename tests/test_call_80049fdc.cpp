// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80049fdc.hpp"
#include <cstdint>
int main() {
    std::uint32_t words[0xc4 / 4] = {};
    words[0xb8 / 4] = 11;
    words[0xbc / 4] = 22;
    words[0xc0 / 4] = 33;
    if (am3d::exe::call_80049fdc(words) != 1) return 1;
    if (words[0x18 / 4] != 11 || words[0x1c / 4] != 22 || words[0x20 / 4] != 33) return 1;
    return 0;
}
