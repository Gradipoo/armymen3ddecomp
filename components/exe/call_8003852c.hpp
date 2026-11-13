// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

struct Call8003852cArgs {
    bool invoke;
    std::uint32_t a0;
    std::int32_t a1;
    std::uint32_t a2;
    std::uint32_t a3;
};

// flag is the byte at 0x800a9ea4. This prefix does not read that address.
// a3 is the incoming fourth argument. fifth is the word at 0x30(sp) after the frame opens.
void call_8003852c(std::uint8_t flag, std::uint32_t a0, std::int32_t a1, std::uint32_t a2,
                   std::uint32_t a3, std::uint32_t fifth, Call8003852cArgs& args);

}
