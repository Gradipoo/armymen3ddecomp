// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800793d4.hpp"
int main() {
    std::uint32_t a=1,b=1,c=1,d=1;
    if (am3d::exe::call_800793d4(a,b,c,d) != 0xffffffffu) return 1;
    if (a||b||c||d!=0xffffffffu) return 2;
    return 0;
}
