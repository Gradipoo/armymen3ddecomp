// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800253a4.hpp"

#include "call_8007c03c.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-800253a4.md.
// The load supplies a0. The delay slot supplies a1.
void call_800253a4(std::uint32_t& a0, std::uint32_t& a1) {
    a0 = 0x800ca918u;
    a1 = 0x900u;
    call_8007c03c(a0, a1);
}

}
