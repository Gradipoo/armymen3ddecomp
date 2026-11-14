// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007e1c8.hpp"

#include "call_8007fbbc.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-8007e1c8.md.
// Copy a0, store it, then shift. The jal returns to 0x8007e1f8.
void call_8007e1c8(std::uint32_t& a0, std::uint32_t& a1, std::uint32_t& stored) {
    a1 = a0;
    stored = a1;
    std::uint32_t high = static_cast<std::uint32_t>(
        (static_cast<std::uint64_t>(a1) * 0xaaaaaaabu) >> 32);
    a1 >>= 2;
    a0 = high >> 1;
    call_8007fbbc(a0, a1);
}

}
