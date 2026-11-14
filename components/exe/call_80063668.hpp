// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

// Behavior reference: docs/research/re/call-80063668.md.
void call_80063668(std::uint32_t& a1, std::uint32_t a0);

}
