// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800751d8.hpp"

namespace am3d::exe {

// Other side of beq at 0x800751d0 for the first entry. This boot does not run it.
std::uint32_t call_800751d8(std::uint32_t a0, std::uint32_t a1, std::uint32_t& stack_word,
    std::uint32_t& saved_word) {
    if (a0 >= 0x11u) {
        return 0;
    }
    if (a0 == 4u) {
        return 1;
    }
    if (a0 != 0) {
        // gap: table slots other than index 0 and index 4.
        return 0;
    }
    saved_word = a1;
    if (stack_word != 0) {
        stack_word = 0;
    }
    return 1;
}

}
