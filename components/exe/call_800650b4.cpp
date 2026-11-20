// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800650b4.hpp"

namespace am3d::exe {

Menu650b4Result call_800650b4(std::uint8_t* record, std::uint32_t complemented_a0) {
    Menu650b4Result result{};
    if (record == nullptr) {
        return result;
    }
    const std::uint32_t masked = complemented_a0 & 0x20u;
    result.complemented_bit_0x20 = masked != 0u;
    result.branch_to_650c8 = masked == 0u;
    if (result.branch_to_650c8) {
        record[0x0au] = 0u;
        result.stored_at_0xa = 0u;
        return result;
    }
    record[0x0au] = 0x7fu;
    result.stored_at_0xa = 0x7fu;
    return result;
}

} // namespace am3d::exe