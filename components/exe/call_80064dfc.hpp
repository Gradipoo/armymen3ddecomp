// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

struct MenuLoopBody64dfc {
    std::uint32_t s1;
    std::uint32_t s7;
    bool branch_to_65194;
    bool entered_64e14;
};

// Taken path at 0x80064dfc when 64dd8 masked byte is not 0x80.
// Behavior reference: docs/research/re/call-80064dfc.md.
// stack_word_1c models sp+0x1c for sw/lw; null skips store and load reads zero.
MenuLoopBody64dfc call_80064dfc(std::uint32_t s1, std::uint32_t t1,
                                std::uint32_t* stack_word_1c);

} // namespace am3d::exe