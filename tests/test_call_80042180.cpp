// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80042180.hpp"
int main() {
    std::uint32_t out[5] = {};
    am3d::exe::call_80042180(1, 2, 3, 4, 5, out);
    if (out[0]!=1u || out[1]!=2u || out[2]!=3u || out[3]!=4u || out[4]!=5u) return 1;
    return 0;
}
