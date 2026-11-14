// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80025398.hpp"

using namespace am3d::exe;

int main() {
    std::uint32_t a0 = 0;
    std::uint32_t a1 = 0;
    call_80025398(a0, a1);
    if (a0 != 0x800ca918u) return 1;
    if (a1 != 0x900u) return 2;
    return 0;
}
