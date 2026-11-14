// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

// Behavior reference: docs/research/re/call-8007d3f8.md.
std::uint32_t call_8007d3f8(std::uint32_t a0, std::uint32_t& slot);

}
