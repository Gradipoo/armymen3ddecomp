// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007e1f8.hpp"

#include "call_80025410.hpp"

#include <cstdint>

namespace am3d::exe {

// Behavior reference: docs/research/re/call-8007e1f8.md.
// The load restores the saved return address, 0x80025410.
void call_8007e1f8() {
    std::uint32_t a0 = 0;
    std::uint32_t stored = 0;
    call_80025410(a0, stored);
}

}
