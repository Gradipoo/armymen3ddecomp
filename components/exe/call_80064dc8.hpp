// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

struct MenuLoopBody64dc8 {
    std::uint32_t v0;
    std::uint32_t s1;
    bool branch_to_65194;
    bool entered_64dd8;
};

// Branch body at 0x80064dc8 after 651c8 when sp+0x18 stays below two.
// Behavior reference: docs/research/re/call-80064dc8.md.
// byte_at_s1 is the lbu source for portable tests; null treats the byte as zero.
MenuLoopBody64dc8 call_80064dc8(std::uint32_t s1, const std::uint8_t* byte_at_s1);

} // namespace am3d::exe