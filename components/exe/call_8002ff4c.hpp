// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstddef>
#include <cstdint>

namespace am3d::exe {

inline constexpr std::size_t kCall8002ff4cBytes = 0x64;

struct Call8002ff4cBlock {
    bool entered = false;
    std::int32_t y_low = 0;
    std::int32_t y_high = 0;
    std::int32_t x_low_shift = 0;
    std::int32_t x_high_shift = 0;
    std::int32_t y_low_shift = 0;
    std::int32_t y_high_shift = 0;
    bool x_skipped = false;
    bool y_skipped = false;
    bool called = false;
    std::uint32_t call_a0 = 0;
    const std::uint8_t* call_a1 = nullptr;
    std::uint32_t call_ra = 0;
};

// Words from 0x8002ff4c through the jal delay slot at 0x8003002c.
// Arrival requires the signed word at offset 0x54 to be smaller than the word at 0x60.
Call8002ff4cBlock call_8002ff4c(const std::uint8_t* object);

}
