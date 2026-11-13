// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

// Behavior reference: docs/research/re/call-80060b10.md.
void call_80060b10(std::uint32_t& a0, std::uint32_t& a1, std::uint32_t& a2, std::uint32_t& a3,
    std::uint32_t& s0);

}
