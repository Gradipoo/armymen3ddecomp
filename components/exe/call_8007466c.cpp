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
    const std::uint32_t result = call_80073fb0(0, 0, 0, 0, 0);
    // gap: resume at 0x800746a4. v0 is 0x800.
    return result;
}
}
