// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800650a8.hpp"

namespace am3d::exe {

Menu650a8Result call_800650a8(std::uint8_t* record) {
    Menu650a8Result result{};
    if (record == nullptr) {
        return result;
    }
    constexpr std::uint8_t kDelaySlotByte = 0x80u;
    record[0x0au] = kDelaySlotByte;
    result.stored_at_0xa = kDelaySlotByte;
    return result;
}

} // namespace am3d::exe