// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80079b24.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-80079b24.md.
void call_80079b24(std::uint32_t a0) {
    (void)a0;
    // gap: jal 0x80079270. a0 stays. a1 is the object. a2 is sp+0x10. a3 is sp+0x14.
    // The return address is 0x80079b4c.
}

}
