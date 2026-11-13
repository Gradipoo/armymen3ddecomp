// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800253b0.hpp"

#include "call_8007c03c.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-800253b0.md.
// Four calls use the traced function. The fifth target is still open.
void call_800253b0(Call800253b0Args calls[5]) {
    calls[0] = {0x800ccd18u, 0x900u};
    calls[1] = {0x800cf118u, 0x900u};
    calls[2] = {0u, 1u};
    calls[3] = {0u, 1u};
    for (int index = 0; index < 4; ++index) {
        call_8007c03c(calls[index].a0, calls[index].a1);
    }
    calls[4] = {0x100u, 0x78u};
    // gap: unnamed call at 0x8007e130. a0 is 0x100. a1 is 0x78. The return address is 0x800253f4.
}

}
