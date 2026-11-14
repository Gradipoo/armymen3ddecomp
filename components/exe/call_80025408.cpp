// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80025408.hpp"

#include "call_8007e1c8.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-80025408.md.
// The delay slot supplies a0. a1 arrives as 0x8000.
void call_80025408(std::uint32_t& a0, std::uint32_t& a1, std::uint32_t& stored) {
    a0 = 0x100u;
    call_8007e1c8(a0, a1, stored);
}

}
