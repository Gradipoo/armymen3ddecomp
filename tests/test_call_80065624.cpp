// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80065624.hpp"
int main() {
    std::uint32_t a=1,b=1;
    if (am3d::exe::call_80065624(a,b) != 0x800dd708u) return 1;
    if (a||b) return 2;
    return 0;
}
