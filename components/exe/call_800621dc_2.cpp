// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800621dc_2.hpp"

namespace am3d::exe {

std::uint32_t call_800621dc_2(std::uint32_t& counter, std::uint32_t& slot,
                              std::uint32_t& a0, std::uint32_t& a1,
                              std::uint32_t handler) {
    a1 = counter;
    slot = handler;
    a0 = 0;
    counter += 1;
    // gap: jalr through handler. On this entry that value is 0x8005b3d4.
    // a0 is 0. a1 is 1. The return address is 0x80062238.
    return handler;
}

}
