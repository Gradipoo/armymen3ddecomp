// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstddef>
#include <cstdint>

namespace am3d::exe {

inline constexpr std::uint32_t kCall80010c90Stored = 0x800be768u;
inline constexpr std::size_t kCall80010c90StoreOffset = 0x68;
inline constexpr std::size_t kCall80010c90WordOffset = 0x74;
inline constexpr std::size_t kCall80010c90Bytes = 0x78;

// Stores 0x800be768 at offset 0x68 of the object passed in a0.
// The second argument is the incoming a1. This prefix does not read it.
void call_80010c90(std::uint8_t* object, std::uint32_t second);

}
