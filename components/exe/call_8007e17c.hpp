// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

// Behavior reference: docs/research/re/call-8007e17c.md.
void call_8007e17c(std::uint32_t& a0, std::uint32_t& a1, std::uint32_t& stored_a0,
                   std::uint32_t& stored_a1);

}
