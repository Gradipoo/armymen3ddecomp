// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800651c8.hpp"

namespace am3d::exe {

MenuLoopTaken651c8 call_800651c8(std::uint32_t v0, std::uint32_t* stack_word_18) {
    MenuLoopTaken651c8 result{};
    std::uint32_t t0 = 0u;
    if (stack_word_18 != nullptr) {
        t0 = *stack_word_18;
    }
    result.s1 = v0 + 0x18fau;
    t0 += 1u;
    const bool below_two =
        static_cast<std::int32_t>(t0) < 2;
    result.v0 = below_two ? 1u : 0u;
    if (stack_word_18 != nullptr) {
        *stack_word_18 = t0;
    }
    if (below_two) {
        result.branch_to_64dc8 = true;
    } else {
        result.entered_651e0 = true;
        // gap: instructions at 0x800651e0 are not traced.
    }
    return result;
}

} // namespace am3d::exe