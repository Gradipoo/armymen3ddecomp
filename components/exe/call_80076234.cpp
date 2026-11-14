// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80076234.hpp"

#include "call_80025398.hpp"

#include <cstdint>

namespace am3d::exe {

// Behavior reference: docs/research/re/call-80076234.md.
// The delay slot writes 1 into a0. The return value is not used.
// After SetDispMask returns, ra is 0x80025398.
std::uint32_t call_80076234() {
    // gap: SetDispMask at 0x80086530. a0 is 1. The return address is 0x80076244.
    std::uint32_t a0 = 0;
    std::uint32_t a1 = 0;
    call_80025398(a0, a1);
    return 1;
}

}
