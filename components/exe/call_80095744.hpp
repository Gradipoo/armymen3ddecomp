// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

// Behavior reference: docs/research/re/call-80095744.md.
void call_80095744(std::uint32_t& cleared, std::uint32_t& status, std::uint32_t& mask);

}
