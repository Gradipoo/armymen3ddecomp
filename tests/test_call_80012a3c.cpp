// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80012a3c.hpp"
int main() {
    std::uint32_t dest[11];
    for (auto& w : dest) w = 1;
    std::uint32_t link = 0x800c5538u;
    if (am3d::exe::call_80012a3c(link, dest) != 0x800c5538u) return 1;
    if (link != 0x800c5564u) return 2;
    if (dest[0] || dest[1] != 0xcu || dest[2] != 0xcu || dest[10]) return 3;
    return 0;
}
