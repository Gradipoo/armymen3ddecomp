// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800253fc.hpp"

#include "call_8007e17c.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-800253fc.md.
// The instruction before the jal writes a0. The delay slot writes a1.
void call_800253fc(std::uint32_t& a0, std::uint32_t& a1, std::uint32_t& stored_a0,
                   std::uint32_t& stored_a1) {
    a0 = 1u;
    a1 = 0x8000u;
    call_8007e17c(a0, a1, stored_a0, stored_a1);
}

}
