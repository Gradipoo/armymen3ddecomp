// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80025470.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-80025470.md.
// This site passes the arriving a0. The jal target is still open.
void call_80025470(std::uint32_t& a0) {
    // gap: unnamed call at 0x80060aac. a0 is 0x800d0000. The return address is 0x80025478.
    (void)a0;
}

}
