// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800621dc_2.hpp"

#include "call_8005b3d4.hpp"

namespace am3d::exe {

std::uint32_t call_800621dc_2(std::uint32_t& counter, std::uint32_t& slot,
                              std::uint32_t& a0, std::uint32_t& a1,
                              std::uint32_t handler) {
    a1 = counter;
    slot = handler;
    a0 = 0;
    counter += 1;
    std::uint32_t word = 0;
    (void)call_8005b3d4(word, 1);
    return handler;
}

}
