// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007c03c.hpp"

using namespace am3d::exe;

int main() {
    std::uint32_t a0 = 0x800c8518u;
    std::uint32_t a1 = 0x900u;
    call_8007c03c(a0, a1);
    if (a0 != 0x800c8518u) return 1;
    if (a1 != 0x900u) return 2;
    return 0;
}
