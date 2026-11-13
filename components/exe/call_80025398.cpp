// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80025398.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-80025398.md.
// The load supplies a0. The delay slot supplies a1.
void call_80025398(std::uint32_t& a0, std::uint32_t& a1) {
    a0 = 0x800c8518u;
    a1 = 0x900u;
    // gap: unnamed call at 0x8007c03c. The return address is 0x800253a4.
}

}
