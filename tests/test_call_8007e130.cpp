// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007e130.hpp"

using namespace am3d::exe;

int main() {
    std::uint32_t a0 = 0x100u;
    std::uint32_t a1 = 0x78u;
    call_8007e130(a0, a1);
    if (a0 != 0x100u) return 1;
    if (a1 != 0x78u) return 2;
    return 0;
}
