// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstddef>
#include <cstdint>

namespace am3d::exe {

inline constexpr std::size_t kCall8002fe4cBytes = 0x64;

struct Call8002fe4cPrefix {
    std::int32_t low = 0;
    std::int32_t high = 0;
    std::int32_t pair_low = 0;
    std::int32_t bound = 0;
    bool negative_byte = false;
    bool bound_replaced = false;
    bool delay_less = false;
};

// First 64 instructions at 0x8002fe4c. The second argument is the incoming a1.
// This prefix replaces that register and does not read its old value.
Call8002fe4cPrefix call_8002fe4c(const std::uint8_t* object, std::uint32_t second);

}
