// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

inline constexpr std::uint32_t kCall800381b0Flag = 0x800a9fccu;
inline constexpr std::uint32_t kCall800381b0Table = 0x800a9fd0u;

inline std::uint32_t call_800381b0_slot(std::uint32_t a0) {
    return kCall800381b0Table + (a0 << 2);
}

struct Call800381b0Args {
    bool invoke;
    std::uint32_t target;
    std::uint32_t a0;
    std::int32_t a1;
    std::uint32_t a2;
    std::uint32_t a3;
};

// flag_word is the word at 0x800a9fcc. slot is the word at 0x800a9fdc when a0 is 3.
// node_word is offset 0 of that node. link is offset 4. The handler words are offsets 0 and 4.
void call_800381b0(std::uint32_t& flag_word, std::uint32_t slot, std::uint32_t node_word,
                   std::uint32_t link, std::uint32_t handler_target, std::uint32_t handler_arg,
                   std::uint32_t a0, std::int32_t a1, std::uint32_t a2, Call800381b0Args& args);

}
