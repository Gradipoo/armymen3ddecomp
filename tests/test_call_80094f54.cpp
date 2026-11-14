// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80094f54.hpp"

#include <cstdint>

using namespace am3d::exe;

int main() {
    std::uint32_t a0 = 0x80022c1cu;
    const std::uint32_t ra = call_80094f54(a0);
    if (a0 != 0x80022c1cu || ra != 0x80064598u) return 1;
    return 0;
}
