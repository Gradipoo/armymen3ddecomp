// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800253f4.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-800253f4.md.
// The delay slot supplies a0. The jal target is still open.
void call_800253f4(std::uint32_t& a0) {
    a0 = 0x200u;
    // gap: unnamed call at 0x8007e150. a0 is 0x200. The return address is 0x800253fc.
}

}
