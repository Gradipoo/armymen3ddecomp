// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80096dac.hpp"
int main() {
    std::uint32_t word = 1;
    std::uint8_t low=1, high=1;
    if (am3d::exe::call_80096dac(word, low, high) != 0x4bu) return 1;
    if (word || low || high != 0x4b) return 2;
    return 0;
}
