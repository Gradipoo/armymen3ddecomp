// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800278b8.hpp"
#include <cstdint>
#include <cstring>
int main() {
    std::uint8_t object[0x48] = {};
    am3d::exe::call_800278b8(object);
    std::uint32_t word = 0;
    std::memcpy(&word, object + 0x44, 4);
    if (word != 0x800bffd0u) return 1;
    return 0;
}
