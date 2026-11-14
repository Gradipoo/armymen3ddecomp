// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8002552c.hpp"

int main() {
    std::uint32_t a0 = 0x800638b8u;
    am3d::exe::call_8002552c(a0);
    if (a0 != 3) return 1;
    return 0;
}
