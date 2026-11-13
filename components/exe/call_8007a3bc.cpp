// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007a3bc.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-8007a3bc.md.
std::uint32_t call_8007a3bc(std::uint32_t v0, std::uint32_t s0, Call8007a3bcFn nonzero) {
    if (v0 == 0) return s0;
    // gap: unnamed jalr through s3 at 0x80010db0 when v0 is not 0.
    return nonzero();
}

}
