// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80030dac.hpp"
int main() {
    std::uint32_t x=0,y=0,z=0;
    am3d::exe::call_80030dac(x,y,z,1,2,3);
    if (x!=1u || y!=2u || z!=3u) return 1;
    return 0;
}
