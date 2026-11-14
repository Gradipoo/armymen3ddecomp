// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

// Entry at 0x80079270 for a0 0x8009f388 or 0x8009f3a8. Returns 0.
std::uint32_t call_80079270();

}
