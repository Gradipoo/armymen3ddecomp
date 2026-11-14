// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80075ba8.hpp"
int main() {
    std::uint32_t flag = 0;
    std::uint32_t slot = 0;
    if (am3d::exe::call_80075ba8(0, flag, slot) != 0x10u) return 1;
    return 0;
}
