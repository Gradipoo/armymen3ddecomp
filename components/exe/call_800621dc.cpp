// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800621dc.hpp"

#include "call_80062238.hpp"
#include "call_80075198.hpp"

namespace am3d::exe {

std::uint32_t call_800621dc(std::uint32_t& counter, std::uint32_t& slot,
                            std::uint32_t& a0, std::uint32_t& a1,
                            std::uint32_t handler) {
    slot = handler;
    a0 = 0;
    a1 = 0;
    counter += 1;
    (void)call_80075198();
    std::uint32_t v0 = 1;
    std::uint32_t s0 = 0;
    std::uint32_t s1 = 0x800dd488u;
    std::uint32_t s2 = 0x800e0000u;
    (void)call_80062238(v0, s0, s1, s2, 0x8009f510u, 0x8009f820u, 0x80080000u,
                        0x800254f0u);
    return handler;
}

}
