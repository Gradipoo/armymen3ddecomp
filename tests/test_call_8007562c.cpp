// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007562c.hpp"
int main() {
    std::uint32_t flag = 0, link = 0, slot = 0;
    if (am3d::exe::call_8007562c(0, flag, link, slot) != 2u) return 1;
    if (flag != 2u || link != 0u) return 2;
    return 0;
}
