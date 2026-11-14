// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007571c.hpp"
int main() {
    std::uint32_t flag = 0;
    std::uint32_t slot = 0;
    if (am3d::exe::call_8007571c(flag, slot) != 0x10u) return 1;
    if (flag != 0x10u) return 2;
    return 0;
}
