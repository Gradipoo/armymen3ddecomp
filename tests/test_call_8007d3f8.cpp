// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007d3f8.hpp"

#include <cstdint>

using namespace am3d::exe;

int main() {
    std::uint32_t slot = 0;
    const std::uint32_t loaded = call_8007d3f8(0x80022c1cu, slot);
    if (loaded != 0 || slot != 0x80022c1cu) return 1;
    return 0;
}
