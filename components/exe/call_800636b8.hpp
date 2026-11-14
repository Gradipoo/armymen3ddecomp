// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

// Behavior reference: docs/research/re/call-800636b8.md.
void call_800636b8(std::uint8_t* dest, std::uint32_t& length);

}
