// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80059f88.hpp"
#include <cstdint>
int main() {
    std::uint32_t slot = 0;
    std::uint32_t stored = 0;
    am3d::exe::call_80059f88(0, slot, stored);
    if (slot != 0x800d8458u || stored != 0xffff0000u) return 1;
    am3d::exe::call_80059f88(0x13u, slot, stored);
    if (slot != 0x800d8458u + 7u * 4u || stored != 0xffff0000u) return 1;
    return 0;
}
