// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstddef>
#include <cstdint>

namespace am3d::exe {

using Call80010f00Fn = std::uint32_t (*)(std::uint32_t a0, std::uint32_t a1,
                                         std::uint32_t a2, std::uint32_t a3);

inline constexpr std::size_t kCall80010f00StoreOffset = 0x6c;
inline constexpr std::size_t kCall80010f00Bytes = 0x70;

// Passes the second through fifth arguments to the callee.
// Stores the returned word at offset 0x6c of the first argument.
// Returns that word. The epilogue does not change it.
std::uint32_t call_80010f00(Call80010f00Fn callee, std::uint8_t* first,
                            std::uint32_t second, std::uint32_t third,
                            std::uint32_t fourth, std::uint32_t fifth);

}
