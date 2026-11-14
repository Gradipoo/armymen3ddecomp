// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800445f4.hpp"
int main() {
    std::uint32_t a=9,b=9,c=9;
    if (am3d::exe::call_800445f4(a,b,c) != 1u) return 1;
    if (a!=1u || b!=0u || c!=1u) return 2;
    return 0;
}
