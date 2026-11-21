// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

struct MenuFirstByteBranchResult {
    bool compare_eq_four = false;
};

// Taken path from call_80064f14 when the first table byte is nonzero.
// Behavior reference: docs/research/re/call-80065144.md.
MenuFirstByteBranchResult call_80065144(std::uint32_t compare_word_dd730);

}  // namespace am3d::exe