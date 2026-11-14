// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80025534.hpp"

int main() {
    std::uint32_t a0 = 3;
    am3d::exe::call_80025534(a0);
    if (a0 != 2) return 1;
    return 0;
}
