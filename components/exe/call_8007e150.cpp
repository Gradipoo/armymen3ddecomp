// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007e150.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-8007e150.md.
// This site passes the arriving a0. It does not write it.
void call_8007e150(std::uint32_t& a0) {
    // gap: SetGeomScreen at 0x8008c4fc. a0 is 0x200. The return address is 0x8007e164.
    (void)a0;
}

}
