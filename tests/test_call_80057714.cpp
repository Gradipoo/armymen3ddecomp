// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80057714.hpp"
#include <cstdint>
#include <cstring>
int main() {
    std::uint8_t base[0xa4];
    std::memset(base, 0xab, sizeof base);
    am3d::exe::call_80057714(base);
    std::uint16_t half = 1;
    std::memcpy(&half, base + 0x70, 2);
    if (half != 0x1000) return 1;
    std::memcpy(&half, base + 4, 2);
    if (half != 0) return 1;
    std::memcpy(&half, base + 0x26, 2);
    if (half != 0) return 1;
    std::uint32_t word = 1;
    std::memcpy(&word, base + 0x80, 4);
    if (word != 0) return 1;
    return 0;
}
