// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80062238.hpp"

int main() {
    std::uint32_t v0 = 1;
    std::uint32_t s0 = 0;
    std::uint32_t s1 = 0x800dd488u;
    std::uint32_t s2 = 0x800e0000u;
    std::uint32_t ra = am3d::exe::call_80062238(v0, s0, s1, s2, 0x8009f510u, 0x8009f820u,
                                                0x80080000u, 0x800254f0u);
    if (v0 != 0 || s0 != 0x8009f510u) return 1;
    if (s1 != 0x8009f820u || s2 != 0x80080000u || ra != 0x800254f0u) return 1;
    return 0;
}
