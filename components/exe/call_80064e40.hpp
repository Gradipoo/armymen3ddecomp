// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

struct MenuLoopHead {
    std::uint32_t s6;
    std::uint32_t s3;
    std::uint32_t s2;
    std::uint32_t below_seven;
    std::uint32_t branch_delay_v0;
    bool branch_to_64f14;
    bool entered_64e68;
};

// Behavior reference: docs/research/re/call-80064e40.md.
// pad_get_state is named PadGetState. This block does not enter that body.
// branch_to_64f14 and entered_64e68 record the beq at 0x80064e60 without
// guessing live words beyond the sltiu result.
void call_80064e40(std::uint32_t stack_word_18, std::uint32_t s7,
                   std::uint32_t (*pad_get_state)(std::uint32_t port),
                   MenuLoopHead& head);

}
