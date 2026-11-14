// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007b118.hpp"
int main() {
    std::uint32_t a=0,b=0,c=0;
    am3d::exe::call_8007b118(a,b,c,1,2,3);
    if (a!=1u || b!=2u || c!=3u) return 1;
    return 0;
}
