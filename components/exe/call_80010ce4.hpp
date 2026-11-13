// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstddef>
#include <cstdint>

namespace am3d::exe {

inline constexpr std::size_t kCall80010ce4FieldOffset = 0x6c;
inline constexpr std::size_t kCall80010ce4HalfOffset = 0x70;
inline constexpr std::size_t kCall80010ce4WordOffset = 0x74;
inline constexpr std::size_t kCall80010ce4Bytes = 0x78;

struct Call80010ce4Args {
    bool invoke;
    std::uint32_t a0;
    std::int32_t a1;
    std::uint32_t a2;
    std::uint32_t a3;
    std::uint32_t stack_arg;
};

// When the word at offset 0x74 is not zero, record the call arguments.
// a0 is the object pointer. This prefix does not write the object.
void call_80010ce4(const std::uint8_t* object, Call80010ce4Args& args);

}
