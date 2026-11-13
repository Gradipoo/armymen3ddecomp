// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007e130.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-8007e130.md.
// This site passes the arriving a0 and a1. It does not write them.
void call_8007e130(std::uint32_t& a0, std::uint32_t& a1) {
    // gap: SetGeomOffset at 0x8008c4dc. The return address is 0x8007e140.
    (void)a0;
    (void)a1;
}

}
