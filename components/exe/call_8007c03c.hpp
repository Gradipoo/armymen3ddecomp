// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

// Behavior reference: docs/research/re/call-8007c03c.md.
void call_8007c03c(std::uint32_t& a0, std::uint32_t& a1);

}
