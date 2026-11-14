// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007466c.hpp"
#include "call_80073eec.hpp"
namespace am3d::exe {
std::uint32_t call_80073fb0(std::uint32_t a0, std::uint32_t flag, std::uint32_t hi, std::uint32_t lo,
    std::uint32_t base) {
    (void)a0;
    if ((flag & 0x40u) != 0) {
        return 0;
    }
    if (hi == lo) {
        a0 += 0x800u;
        (void)a0;
    }
    return call_80073eec(base, 0x800u, 0);
}
std::uint32_t call_8007466c() {
    call_80073fb0(0, 0, 0, 0, 0);
    const std::uint32_t result = call_800741b8(2, 0);
    // gap: resume at 0x80074750. v0 is 4. The flag word on this side is 4.
    return result;
}
std::uint32_t call_800741b8(std::uint32_t a0, std::uint32_t link) {
    if ((a0 & 0xffu) != 2u || link != 0) {
        return 0;
    }
    return 4;
}
}
