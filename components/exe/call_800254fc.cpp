// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800254fc.hpp"

#include "call_80025514.hpp"
#include "call_8002552c.hpp"
#include "call_800621dc_2.hpp"

namespace am3d::exe {

void call_800254fc(std::uint32_t& a0, std::uint32_t& s2, std::uint32_t& cleared) {
    a0 = 0x8005b3d4u;
    s2 = 0x8009f820u;
    cleared = 0;
    std::uint32_t counter = 1;
    std::uint32_t slot = 0;
    std::uint32_t a1 = 0;
    (void)call_800621dc_2(counter, slot, a0, a1, a0);
    call_80025514(a0);
    call_8002552c(a0);
}

}
