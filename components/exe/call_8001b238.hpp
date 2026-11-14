// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

// Wrapper at 0x8001b238. On the cited entry a0 is 0xd0.
void call_8001b238(std::uint32_t a0);

}
