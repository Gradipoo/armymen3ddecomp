// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800253fc.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-800253fc.md.
// The instruction before the jal writes a0. The delay slot writes a1.
void call_800253fc(std::uint32_t& a0, std::uint32_t& a1) {
    a0 = 1u;
    a1 = 0x8000u;
    // gap: unnamed call at 0x8007e17c. a0 is 1. a1 is 0x8000. The return address is 0x80025408.
}

}
