// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80074b4c.hpp"
int main() {
    std::uint32_t c0 = 0, c4 = 0, c8 = 0;
    am3d::exe::call_80074b4c(c0, c4, c8);
    if (c0 != 0x80074a90u) return 1;
    return 0;
}
