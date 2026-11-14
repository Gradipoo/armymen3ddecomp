// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8005775c.hpp"
#include <cstdint>
#include <cstring>
int main() {
    std::uint8_t base[0xa4];
    std::memset(base, 0xab, sizeof base);
    if (am3d::exe::call_8005775c(base) != base) return 1;
    std::uint16_t half = 1;
    std::memcpy(&half, base + 0xa0, 2);
    if (half != 0x1000) return 1;
    std::memcpy(&half, base + 16, 2);
    if (half != 0) return 1;
    return 0;
}
