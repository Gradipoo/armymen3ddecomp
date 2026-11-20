// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80064dec.hpp"

namespace am3d::exe {

MenuLoopBody64dec call_80064dec(std::uint32_t s1, std::uint32_t* stack_word_1c) {
    MenuLoopBody64dec result{};
    constexpr std::uint32_t kStackWord = 4u;
    if (stack_word_1c != nullptr) {
        *stack_word_1c = kStackWord;
    }
    result.s1 = s1 + 1u;
    std::uint32_t t0 = 0u;
    if (stack_word_1c != nullptr) {
        t0 = *stack_word_1c;
    }
    result.s7 = 0u;
    if (t0 == 0u) {
        result.branch_to_65194 = true;
    } else {
        result.entered_64e14 = true;
    }
    return result;
}

} // namespace am3d::exe