// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007569c.hpp"
int main() {
    std::uint32_t flag = 0, link = 0, c0 = 0, c8 = 0, cd = 0;
    am3d::exe::call_8007569c(0, flag, link, c0, c8, cd);
    if (flag != 0u || link != 0u || cd != 2u) return 1;
    return 0;
}
