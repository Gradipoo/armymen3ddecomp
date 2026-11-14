// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007b128.hpp"
int main() {
    std::uint32_t a=1,b=2,c=3;
    if (am3d::exe::call_8007b128(a,b,c,4,5,6) != 7u) return 1;
    if (a!=5u || c!=9u) return 2;
    return 0;
}
