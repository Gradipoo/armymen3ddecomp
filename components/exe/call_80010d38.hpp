// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstddef>
#include <cstdint>

namespace am3d::exe {

inline constexpr std::size_t kCall80010d38WordOffset = 0x74;
inline constexpr std::size_t kCall80010d38Bytes = 0x78;

using Call80010d38Fn = void (*)(std::uint32_t a0);
using Call80010d74Fn = void (*)(std::uint32_t a0);

// When the second argument is zero, a nonzero word at offset 0x74 is passed
// to callee. This path then stores zero at that offset. A nonzero second
// argument is passed to nonzero. The continuation of that call stays open.
void call_80010d38(std::uint8_t* object, std::uint32_t second, Call80010d38Fn callee,
                   Call80010d74Fn nonzero);

}
