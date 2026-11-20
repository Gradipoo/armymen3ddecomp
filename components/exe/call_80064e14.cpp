// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80064e14.hpp"

namespace am3d::exe {

MenuLoopReentry64e14 call_80064e14(std::uint32_t s5, std::uint32_t stack_word_18,
                                   std::uint32_t s7, std::uint32_t* stack_word_28,
                                   std::uint32_t (*pad_get_state)(std::uint32_t port)) {
    MenuLoopReentry64e14 result{};
    constexpr std::uint32_t kRecordBase = 0x800dd748u;
    constexpr std::uint32_t kAuxBase = 0x800dd708u;
    result.s0 = kRecordBase + (s5 * 124u);
    const std::uint32_t s5_scaled = s5 * 4u;
    result.s4 = kAuxBase + s5_scaled;
    if (stack_word_28 != nullptr) {
        *stack_word_28 = s5_scaled;
    }
    call_80064e40(stack_word_18, s7, pad_get_state, result.head);
    return result;
}

} // namespace am3d::exe