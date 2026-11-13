// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80010e00.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-80010e00.md.
void call_80010e00(Call80010e00Fn callee) {
    const std::uint32_t a0 = 0x8009f368u;
    const std::uint32_t a1 = 1u;
    const std::uint32_t a2 = 0x80010db0u;
    const std::uint32_t a3 = 0u;
    // gap: unnamed callee at 0x8007a384.
    callee(a0, a1, a2, a3);
}

}
