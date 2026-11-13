// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

// Wrapper at 0x8001b298. The argument is the incoming a0.
void call_8001b298(std::uint32_t pointer);

}
