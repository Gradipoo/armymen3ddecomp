// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80028da4.hpp"
int main() {
    std::uint32_t a=1,b=1;
    if (am3d::exe::call_80028da4(0,0,a,b) != 0x800d25e0u) return 1;
    if (a||b) return 2;
    return 0;
}
