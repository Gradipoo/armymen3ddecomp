// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

struct MenuCompareFourResult {
    std::uint32_t masked_complement;
    bool branch_to_65168;
    std::uint32_t v0;
};

// Fallthrough at 0x80064f78 when compare word equals four at 0x80064f70.
// Behavior reference: docs/research/re/call-80064f78.md.
MenuCompareFourResult call_80064f78(std::uint32_t complemented_a0);

}