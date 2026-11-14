// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800253f4.hpp"

#include "call_800253fc.hpp"
#include "call_8007e150.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-800253f4.md.
// The delay slot supplies a0.
void call_800253f4(std::uint32_t& a0) {
    a0 = 0x200u;
    call_8007e150(a0);
    std::uint32_t a1 = 0;
    std::uint32_t stored_a0 = 0;
    std::uint32_t stored_a1 = 0;
    call_800253fc(a0, a1, stored_a0, stored_a1);
}

}
