// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80025408.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-80025408.md.
// The delay slot supplies a0. The jal target is still open.
void call_80025408(std::uint32_t& a0) {
    a0 = 0x100u;
    // gap: unnamed call at 0x8007e1c8. a0 is 0x100. a1 stays 0x8000. The return address is 0x80025410.
}

}
