// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

struct MenuLoopTaken651c8 {
    std::uint32_t s1;
    std::uint32_t v0;
    bool branch_to_64dc8;
    bool entered_651e0;
};

// Taken path at 0x800651c8 when s5 is nonzero at 0x80065194.
// Behavior reference: docs/research/re/call-800651c8.md.
// v0 is live after the delay slot at 0x80065198 (lui 0x800e).
// stack_word_18 models sp+0x18 load, increment, and delay-slot store.
MenuLoopTaken651c8 call_800651c8(std::uint32_t v0, std::uint32_t* stack_word_18);

} // namespace am3d::exe