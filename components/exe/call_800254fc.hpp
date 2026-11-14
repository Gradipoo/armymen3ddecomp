// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

// Behavior reference: docs/research/re/call-800254fc.md.
void call_800254fc(std::uint32_t& a0, std::uint32_t& s2, std::uint32_t& cleared);

}
