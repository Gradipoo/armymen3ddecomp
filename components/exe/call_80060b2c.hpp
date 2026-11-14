// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

// Behavior reference: docs/research/re/call-80060b2c.md.
std::uint32_t call_80060b2c(std::uint32_t& a0, std::uint32_t& word_14, std::uint32_t& word_18,
    std::uint32_t& stored, std::uint32_t& s0);

}
