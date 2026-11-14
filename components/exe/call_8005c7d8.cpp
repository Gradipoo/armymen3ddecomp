// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8005c7d8.hpp"
#include "call_8005c1a0.hpp"
namespace am3d::exe {
void call_8005c7d8(std::uint32_t a0, std::uint32_t a1) {
    (void)a1;
    call_8005c1a0(a0, 0x10u, 1u);
    // gap: beq at 0x8005c808. v0 from call_8005c1a0 is not stated.
}
}
