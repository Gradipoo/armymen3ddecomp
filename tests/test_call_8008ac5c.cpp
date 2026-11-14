// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8008ac5c.hpp"
int main() {
    std::uint8_t a=0,b=0;
    if (am3d::exe::call_8008ac5c(a,b) != 0x40u) return 1;
    if (a!=3 || b!=0x40) return 2;
    return 0;
}
