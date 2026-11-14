// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

// Behavior reference: docs/research/re/call-8002553c.md.
void call_8002553c(std::uint32_t& a0, std::uint32_t& s0);

}
