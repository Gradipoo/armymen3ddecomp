// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007c2b8.hpp"
int main() {
    std::uint32_t word = 1;
    if (am3d::exe::call_8007c2b8(0, word) != 0x800e0000u) return 1;
    if (word) return 2;
    return 0;
}
