// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

// Behavior reference: docs/research/re/call-80025390.md.
std::uint32_t call_after_display_clear(std::uint32_t compare_result);

}
