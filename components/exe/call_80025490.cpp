// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80025490.hpp"

#include "call_800254f0.hpp"
#include "call_800254fc.hpp"
#include "call_800621dc.hpp"

namespace am3d::exe {

void call_80025490(std::uint32_t& a0) {
    a0 = 0x80075198u;
    std::uint32_t counter = 0;
    std::uint32_t slot = 0;
    std::uint32_t a1 = 0;
    (void)call_800621dc(counter, slot, a0, a1, a0);
    call_800254f0(a0);
    std::uint32_t s2 = 0x80080000u;
    std::uint32_t cleared = 1;
    call_800254fc(a0, s2, cleared);
}

}
