// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

// Behavior reference: docs/research/re/call-80060b4c.md.
void call_80060b4c(std::uint32_t a0, std::uint32_t& stored);

}
