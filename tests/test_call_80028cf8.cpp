// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80028cf8.hpp"
int main() {
    std::uint32_t a=1,b=1,c=1,d=1;
    if (am3d::exe::call_80028cf8(0,0,0,0,a,b,c,d) != 0x800d25e0u) return 1;
    if (a||b||c||d) return 2;
    return 0;
}
