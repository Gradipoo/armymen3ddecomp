// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

struct MenuLoopHead {
    std::uint32_t s6;
    std::uint32_t s3;
    std::uint32_t s2;
    std::uint32_t below_seven;
};

// Behavior reference: docs/research/re/call-80064e40.md.
// pad_get_state is named PadGetState. This block does not enter that body.
void call_80064e40(std::uint32_t stack_word_18, std::uint32_t s7,
                   std::uint32_t (*pad_get_state)(std::uint32_t port),
                   MenuLoopHead& head);

}
