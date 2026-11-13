// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80025410.hpp"

using namespace am3d::exe;

int main() {
    std::uint32_t a0 = 0;
    call_80025410(a0);
    if (a0 != 0x800d1598u) return 1;
    return 0;
}
