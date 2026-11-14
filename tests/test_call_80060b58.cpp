// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80060b58.hpp"

#include <cstdint>

using namespace am3d::exe;

int main() {
    const std::uint32_t a0 = 0x1000u;
    std::uint16_t slot0 = 1;
    std::uint16_t slot6 = 1;
    std::uint16_t slot12 = 1;
    std::uint16_t slot2 = 1;
    std::uint16_t slot8 = 1;
    std::uint16_t slot14 = 1;
    call_80060b58(a0, slot0, slot6, slot12, slot2, slot8, slot14);
    if (slot0 != 0x1000u || slot6 != 0x1000u || slot12 != 0x1000u || slot2 != 0x1000u ||
        slot8 != 0x1000u || slot14 != 0x1000u) {
        return 1;
    }
    return 0;
}
