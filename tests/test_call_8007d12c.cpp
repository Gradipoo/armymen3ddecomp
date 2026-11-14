// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007d12c.hpp"

int main() {
    std::uint32_t word = 9;
    std::uint32_t s0 = 3;
    std::uint32_t ra = am3d::exe::call_8007d12c(word, s0, 0x8009f510u, 0x80025534u);
    if (word != 0 || s0 != 0x8009f510u || ra != 0x80025534u) return 1;
    return 0;
}
