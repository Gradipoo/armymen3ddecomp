// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800961c4.hpp"
int main() {
    std::uint32_t word = 0;
    std::uint8_t byte = 0;
    am3d::exe::call_800961c4(9, 0x102u, word, byte);
    if (word != 9u || byte != 2) return 1;
    return 0;
}
