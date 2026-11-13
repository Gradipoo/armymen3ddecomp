// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstddef>
#include <cstdint>

namespace am3d::exe {

inline constexpr std::size_t kCall800302a4ByteOffset = 0x35;
inline constexpr std::size_t kCall800302a4Bytes = 0x36;

// Reads the signed byte at offset 0x35 of the object passed in a0.
// The second argument is the incoming a1. This prefix does not read it.
void call_800302a4(std::uint8_t* object, std::uint32_t second);

}
