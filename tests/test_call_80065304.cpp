// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80065304.hpp"
int main() {
    std::uint8_t base[16] = {};
    if (am3d::exe::call_80065304(0, 1, 2, base) != 0x800dd708u) return 1;
    if (base[8] != 2 || base[9] != 1) return 2;
    return 0;
}
