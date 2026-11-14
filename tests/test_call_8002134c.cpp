// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8002134c.hpp"
#include <cstdint>
#include <cstring>
int main() {
    std::uint8_t object[8] = {};
    if (am3d::exe::call_8002134c(object, 0x11u) != object) return 1;
    std::uint32_t word = 0;
    std::memcpy(&word, object, 4);
    if (word != 0x11u) return 1;
    return 0;
}
