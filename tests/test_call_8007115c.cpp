// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007115c.hpp"
int main() {
    std::uint16_t a=0,b=0,c=0;
    am3d::exe::call_8007115c(0xffffu, a, b, c);
    if (a != 0xffffu || b != 0x7f7fu || c != 0x3f3fu) return 1;
    return 0;
}
