// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

// Behavior reference: docs/research/re/call-80064588.md.
std::uint32_t call_80064588(std::uint32_t& a0);

}
