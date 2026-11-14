// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8006f12c.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-8006f12c.md.
// scratch points at 0x1f800380. Nineteen words cover through 0x1f8003c8.
void call_8006f12c(std::uint32_t* scratch) {
    for (int i = 0; i < 19; ++i) {
        scratch[i] = 0;
    }
    scratch[2] = 0x200u;
    scratch[7] = 0x200u;
    scratch[12] = 0x200u;
}

}
