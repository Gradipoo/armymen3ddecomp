// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80028dc4.hpp"
int main() {
    std::uint32_t word = 1;
    if (am3d::exe::call_80028dc4(0, word) != 0x800d0000u) return 1;
    if (word != 0u) return 2;
    return 0;
}
