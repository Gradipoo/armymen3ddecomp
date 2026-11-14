// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800621dc_2.hpp"

#include "call_8005b3d4.hpp"
#include "call_80062238_2.hpp"

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
    std::uint32_t v0 = 1;
    std::uint32_t s0 = 1;
    std::uint32_t s1 = 0x800dd488u;
    std::uint32_t s2 = 0x800e0000u;
    (void)call_80062238_2(v0, s0, s1, s2, 0x8009f510u, 0x8009f820u, 0x8009f820u,
                          0x80025514u);
    return handler;
}

}
