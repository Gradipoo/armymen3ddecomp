// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

struct MenuLoopFallthrough {
    bool branch_to_651c8;
    bool entered_6519c;
    std::uint32_t v0;
};

// Behavior reference: docs/research/re/call-80065194.md.
// s5 is the post-tail index word from MenuInputScanState (retail s5).
MenuLoopFallthrough call_80065194(std::uint32_t s5);

} // namespace am3d::exe