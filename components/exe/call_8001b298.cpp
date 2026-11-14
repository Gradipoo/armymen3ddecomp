// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8001b298.hpp"

namespace am3d::exe {

void __builtin_delete(std::uint32_t pointer) {
    (void)pointer;
}

// Behavior reference: docs/research/re/call-8001b298.md.
// The body at 0x8001b214 stays in the SDK. The return address is 0x8001b2a8.
void call_8001b298(std::uint32_t pointer) {
    __builtin_delete(pointer);
}

}
