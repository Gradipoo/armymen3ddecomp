// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007e17c.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-8007e17c.md.
// A non-positive a0 is cleared. This boot leaves a0 at 1, then stores both words.
void call_8007e17c(std::uint32_t& a0, std::uint32_t& a1, std::uint32_t& stored_a0,
                   std::uint32_t& stored_a1) {
    if (static_cast<std::int32_t>(a0) <= 0) {
        a0 = 0;
    }
    stored_a0 = a0;
    stored_a1 = a1;
}

}
