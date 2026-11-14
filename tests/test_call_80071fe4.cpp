// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80071fe4.hpp"
int main() {
    std::uint32_t low=0, high=0;
    am3d::exe::call_80071fe4(3, 4, low, high);
    if (low != 3u || high != 4u) return 1;
    return 0;
}
