// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8005be64.hpp"
int main() {
    std::uint32_t slot = 0, flag = 0;
    if (am3d::exe::call_8005be64(slot, flag) != 0x800d89b8u) return 1;
    if (flag != 0u) return 2;
    return 0;
}
