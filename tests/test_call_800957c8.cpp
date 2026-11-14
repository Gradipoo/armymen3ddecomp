// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800957c8.hpp"

int main() {
    std::uint32_t argument = 0x80022c1cu;
    std::uint32_t handler = am3d::exe::call_800957c8(argument, 0, 0);
    if (argument != 0xf0u || handler != 0) return 1;
    return 0;
}
