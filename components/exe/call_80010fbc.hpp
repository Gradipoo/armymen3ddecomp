// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstddef>
#include <cstdint>

namespace am3d::exe {

inline constexpr std::uint32_t kCall80010fbcStored = 0x800c005cu;
inline constexpr std::size_t kCall80010fbcStoreOffset = 0x68;
inline constexpr std::size_t kCall80010fbcBytes = 0x6c;

// Stores 0x800c005c at offset 0x68 of the object passed in a0.
void call_80010fbc(std::uint8_t* object);

}
