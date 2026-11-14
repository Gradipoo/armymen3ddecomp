// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80075c64.hpp"
int main() {
    std::uint32_t flag = 0;
    std::uint32_t slot = 0;
    (void)am3d::exe::call_80075c64(0, 0, flag, slot);
    if (slot != 0x800759c8u) return 1;
    return 0;
}
