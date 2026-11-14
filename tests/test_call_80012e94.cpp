// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80012e94.hpp"
#include <cstdint>
int main() {
    std::uint8_t object[0x120] = {};
    std::uint8_t table[0x20] = {};
    am3d::exe::call_80012e94(object, 0, table);
    std::uint32_t at_68 = object[0x68] | (object[0x69] << 8) | (object[0x6a] << 16) | (object[0x6b] << 24);
    std::uint32_t at_a4 = object[0xa4] | (object[0xa5] << 8) | (object[0xa6] << 16) | (object[0xa7] << 24);
    if (at_68 != 0x800be980u) return 1;
    if (at_a4 != 0x1000u) return 2;
    if (object[0x10c] != 1) return 3;
    return 0;
}
