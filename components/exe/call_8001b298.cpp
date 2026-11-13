// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8001b298.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-8001b298.md.
void call_8001b298(std::uint32_t pointer) {
    (void)pointer;
    // gap: __builtin_delete at 0x8001b214. a0 is pointer. The return address is 0x8001b2a8.
}

}
