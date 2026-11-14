// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80012f94.hpp"
int main() {
    std::uint8_t object[0x134] = {};
    object[0x120] = 9;
    am3d::exe::call_80012f94(object);
    if (object[0x120] != 0x21) return 1;
    std::uint32_t at_7c = object[0x7c] | (object[0x7d] << 8) | (object[0x7e] << 16) | (object[0x7f] << 24);
    if (at_7c != 0x400u) return 2;
    return 0;
}
