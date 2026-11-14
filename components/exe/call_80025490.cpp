// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80025490.hpp"

#include "call_800621dc.hpp"

namespace am3d::exe {

void call_80025490(std::uint32_t& a0) {
    a0 = 0x80075198u;
    std::uint32_t counter = 0;
    std::uint32_t slot = 0;
    std::uint32_t a1 = 0;
    (void)call_800621dc(counter, slot, a0, a1, a0);
}

}
