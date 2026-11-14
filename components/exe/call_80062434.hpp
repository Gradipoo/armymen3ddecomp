// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

// Behavior reference: docs/research/re/call-80062434.md.
void call_80062434(std::uint8_t* dest, std::uint32_t& a0, std::uint32_t source);

}
