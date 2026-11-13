// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

// Behavior reference: docs/research/re/call-80076234.md.
// Returns the SetDispMask argument from this site.
std::uint32_t call_80076234();

}
