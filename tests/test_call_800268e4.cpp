// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800268e4.hpp"
#include <cstdint>
#include <cstring>
int main() {
    std::uint8_t object[0x28] = {};
    am3d::exe::call_800268e4(object);
    std::uint32_t word = 0;
    std::memcpy(&word, object + 0x24, 4);
    if (word != 0x800bff68u) return 1;
    return 0;
}
