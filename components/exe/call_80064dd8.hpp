// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

struct MenuLoopBody64dd8 {
    std::uint32_t v0;
    std::uint32_t v1;
    std::uint32_t t1;
    bool branch_to_64dfc;
    bool entered_64dec;
};

// Fallthrough at 0x80064dd8 when 64dc8 loaded byte is zero.
// Behavior reference: docs/research/re/call-80064dd8.md.
// byte_at_s1 is the lbu source for portable tests; null treats the byte as zero.
MenuLoopBody64dd8 call_80064dd8(std::uint32_t s1, const std::uint8_t* byte_at_s1);

} // namespace am3d::exe