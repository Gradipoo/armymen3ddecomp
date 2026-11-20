// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80065098.hpp"

#include <cstring>

namespace am3d::exe {

MenuS6TakenPath call_80065098(std::uint8_t* record, std::uint32_t complemented_a0,
                                std::uint32_t v0, std::uint32_t& table_cursor_s1) {
    MenuS6TakenPath result{};
    if (record == nullptr) {
        return result;
    }
    std::memcpy(record, &v0, sizeof(v0));
    result.stored_word = v0;
    const std::uint32_t masked = complemented_a0 & 0x80u;
    result.complemented_bit_0x80 = masked != 0u;
    result.branch_to_650b4 = masked == 0u;
    table_cursor_s1 += 4u;
    return result;
}

}