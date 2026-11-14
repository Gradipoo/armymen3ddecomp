// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8002541c.hpp"

using namespace am3d::exe;

int main() {
    std::uint32_t a0 = 0x800d1598u;
    std::uint32_t v0 = 0;
    call_8002541c(a0, 1u, v0);
    if (a0 != 0x800d0000u) return 1;
    if (v0 != 1u) return 2;
    a0 = 0x800d1598u;
    call_8002541c(a0, 0u, v0);
    if (a0 != 0x8009f444u) return 3;
    if (v0 != 0u) return 4;
    return 0;
}
