// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80030ba4.hpp"
int main() {
    std::uint32_t x=1,y=2,z=3;
    if (am3d::exe::call_80030ba4(x,y,z,0x10,0x20,0x30) != 0x22u) return 1;
    if (x!=0x11u || z!=0x33u) return 2;
    return 0;
}
