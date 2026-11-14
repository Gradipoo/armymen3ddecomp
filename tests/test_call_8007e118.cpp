// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007e118.hpp"

using namespace am3d::exe;

int main() {
    std::uint32_t a0 = 0x800d1598u;
    std::uint32_t stored = 0;
    call_8007e118(a0, stored);
    if (stored != 0x800d1598u) return 1;
    if (a0 != 0x800d1598u) return 2;
    return 0;
}
