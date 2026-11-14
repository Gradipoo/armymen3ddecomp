// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80060b3c.hpp"

#include <cstdint>

using namespace am3d::exe;

int main() {
    std::uint32_t s0 = 0x800dd2d8u;
    const std::uint32_t returned = call_80060b3c(0x80025478u, s0, 0x8009f510u);
    if (s0 != 0x8009f510u || returned != 0x80025478u) return 1;
    return 0;
}
