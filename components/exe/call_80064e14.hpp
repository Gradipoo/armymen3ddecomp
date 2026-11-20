// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include "call_80064e40.hpp"

#include <cstdint>

namespace am3d::exe {

struct MenuLoopReentry64e14 {
    std::uint32_t s0;
    std::uint32_t s4;
    MenuLoopHead head;
};

// Fallthrough at 0x80064e14 when the shared beq at 0x80064e0c is not taken.
// Behavior reference: docs/research/re/call-80064e14.md.
// s5 is retail index (MenuInputScanState::index). stack_word_28 models sp+0x28.
MenuLoopReentry64e14 call_80064e14(std::uint32_t s5, std::uint32_t stack_word_18,
                                   std::uint32_t s7, std::uint32_t* stack_word_28,
                                   std::uint32_t (*pad_get_state)(std::uint32_t port));

} // namespace am3d::exe