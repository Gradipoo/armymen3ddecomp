// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstddef>
#include <cstdint>

namespace am3d::exe {

inline constexpr std::uint32_t kCall8002fc2cStored = 0x800c005cu;
inline constexpr std::size_t kCall8002fc2cStoreOffset = 0x68;
inline constexpr std::size_t kCall8002fc2cBytes = 0x6c;

// Stores 0x800c005c at offset 0x68 of the object passed in a0.
// The second argument is the incoming a1. This prefix does not read it.
void call_8002fc2c(std::uint8_t* object, std::uint32_t second);

}
