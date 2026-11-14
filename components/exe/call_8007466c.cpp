// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007466c.hpp"
namespace am3d::exe {
std::uint32_t call_80073fb0(std::uint32_t a0, std::uint32_t flag, std::uint32_t hi, std::uint32_t lo,
    std::uint32_t base) {
    (void)a0;
    (void)flag;
    (void)hi;
    (void)lo;
    (void)base;
    // gap: unnamed callee at 0x80073fb0. a0 is 0. The return address is 0x800746a4.
    return 0;
}
std::uint32_t call_8007466c() {
    return call_80073fb0(0, 0, 0, 0, 0);
}
}
