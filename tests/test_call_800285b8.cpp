// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800285b8.hpp"
int main() {
    std::uint32_t word = 1;
    if (am3d::exe::call_800285b8(0, word) != 0x800d0000u) return 1;
    if (word != 0u) return 2;
    return 0;
}
