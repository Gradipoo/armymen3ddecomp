// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80064e40.hpp"

namespace am3d::exe {

void call_80064e40(std::uint32_t stack_word_18, std::uint32_t s7,
                   std::uint32_t (*pad_get_state)(std::uint32_t port),
                   MenuLoopHead& head) {
    head.s6 = 0u;
    head.s3 = (stack_word_18 << 4u) | s7;
    head.s2 = pad_get_state(head.s3);
    head.below_seven = head.s2 < 7u ? 1u : 0u;
    // gap: beq at 0x80064e60 is not followed.
}

}
