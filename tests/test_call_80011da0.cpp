// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80011da0.hpp"
int main() {
    std::uint16_t a=1,b=1,c=1;
    am3d::exe::call_80011da0(a,b,c);
    if (a||b||c) return 1;
    return 0;
}
