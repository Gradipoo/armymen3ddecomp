// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80096d38.hpp"
int main() {
    std::uint32_t word = 1;
    std::uint8_t low=1, high=1;
    if (am3d::exe::call_80096d38(word, low, high) != 0x45u) return 1;
    if (word || low || high != 0x45) return 2;
    return 0;
}
