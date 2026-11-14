// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8003cd44.hpp"
int main() {
    std::uint32_t x=0,y=0,z=0;
    am3d::exe::call_8003cd44(x,y,z,4,5,6);
    if (x!=4u || y!=5u || z!=6u) return 1;
    return 0;
}
