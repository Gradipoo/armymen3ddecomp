// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

// Behavior reference: docs/research/re/call-80077fdc.md.
std::uint32_t call_80077fdc(std::uint32_t& word, std::uint32_t a0, std::uint32_t saved_ra);

}
