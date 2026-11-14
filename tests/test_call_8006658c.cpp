// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8006658c.hpp"
int main() {
    std::uint32_t word = 1;
    if (am3d::exe::call_8006658c(word) != 0x800e0000u) return 1;
    if (word) return 2;
    return 0;
}
