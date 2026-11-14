// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80025478.hpp"

#include <cstdint>

using namespace am3d::exe;

int main() {
    std::uint32_t a0 = 0x1000u;
    std::uint32_t stored = 1;
    const std::uint32_t loaded = call_80025478(a0, stored);
    if (a0 != 0 || stored != 0x80022c1cu || loaded != 0) return 1;
    return 0;
}
