// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

// Behavior reference: docs/research/re/call-8006471c.md.
std::uint32_t call_8006471c(std::uint32_t index, std::uint32_t bits, std::uint32_t& masked);

}
