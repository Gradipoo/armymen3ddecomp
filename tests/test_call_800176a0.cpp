// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800176a0.hpp"
#include <cstdint>
int main() {
    std::uint32_t slot = 1;
    std::uint32_t cleared = 1;
    am3d::exe::call_800176a0(slot, cleared);
    if (slot != 0x800beae8u || cleared != 0) return 1;
    return 0;
}
