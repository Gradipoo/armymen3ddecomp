// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007c03c.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-8007c03c.md.
// This site passes the arriving a0 and a1. It does not write them.
void call_8007c03c(std::uint32_t& a0, std::uint32_t& a1) {
    // gap: ClearOTagR at 0x80086ab4. The return address is 0x8007c04c.
    (void)a0;
    (void)a1;
}

}
