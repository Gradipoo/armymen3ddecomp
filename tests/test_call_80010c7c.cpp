// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80010c7c.hpp"
int main() {
    std::uint32_t a=1,b=1; std::uint16_t c=1,d=1;
    am3d::exe::call_80010c7c(a,c,d,b);
    if (a||b||c||d) return 1;
    return 0;
}
