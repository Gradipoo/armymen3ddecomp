// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8008c29c.hpp"
int main() {
    std::uint32_t src[3] = {1,2,3};
    std::uint32_t dest[3] = {};
    if (am3d::exe::call_8008c29c(dest, src) != dest) return 1;
    if (dest[0]!=1u || dest[2]!=3u) return 2;
    return 0;
}
