// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

// Behavior reference: docs/research/re/call-80094f64.md.
std::uint32_t call_80094f64(std::uint32_t saved_ra);

}
