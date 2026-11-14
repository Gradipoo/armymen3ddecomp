// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

// Behavior reference: docs/research/re/call-8007abf8.md.
// slot is nine halfwords. The three words follow those halfwords, after two unwritten bytes.
void call_8007abf8(std::uint32_t a1, std::uint32_t a2, std::uint32_t a3, std::uint16_t slot[9],
    std::uint32_t& word_14, std::uint32_t& word_18, std::uint32_t& word_1c);

}
