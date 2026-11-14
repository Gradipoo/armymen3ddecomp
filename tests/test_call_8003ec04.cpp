// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8003ec04.hpp"
int main() {
    std::uint32_t low=1, high=1;
    if (am3d::exe::call_8003ec04(7, low, high) != 0u) return 1;
    if (low!=0u || high!=7u) return 2;
    return 0;
}
