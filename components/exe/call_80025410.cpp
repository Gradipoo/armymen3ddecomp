// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80025410.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-80025410.md.
// The lui and the delay slot supply a0. The jal target is still open.
void call_80025410(std::uint32_t& a0) {
    a0 = 0x800d1598u;
    // gap: unnamed call at 0x8007e118. a0 is 0x800d1598. The return address is 0x8002541c.
}

}
