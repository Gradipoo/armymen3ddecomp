// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstddef>
#include <cstdint>

namespace am3d::exe {

inline constexpr std::size_t kCall8002fb9cBytes = 0x38;
inline constexpr std::size_t kCall8002fb9cTableBytes = 0x20;
inline constexpr std::size_t kCall8002fb9cCopyOffset = 0x4;
inline constexpr std::size_t kCall8002fb9cCopyWords = 8;

// Copies eight words from the table at 0x8009f0b4 onto the object.
// The second argument is the incoming a1. This prefix does not read it.
void call_8002fb9c(std::uint8_t* object, std::uint32_t second,
                   const std::uint8_t* table);

}
