// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007a3b0.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-8007a3b0.md.
void call_8007a3b0(std::uint32_t s1, std::uint32_t* slot10, std::uint32_t a2,
                   std::uint32_t a3, Call8007a3b0Fn callee) {
    const std::uint32_t a0 = s1;
    // gap: unnamed callee at 0x8007a2b0.
    callee(a0, slot10, a2, a3);
}

}
