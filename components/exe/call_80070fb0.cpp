// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80070fb0.hpp"

#include "call_8006f12c.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-80070fb0.md.
// The 92 bytes match 0x8006f12c.
void call_80070fb0(std::uint32_t* scratch) {
    call_8006f12c(scratch);
}

}
