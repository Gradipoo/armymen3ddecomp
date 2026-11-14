// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

// Body at 0x8001b17c. The cited entry passes the arriving a0 as a1.
void call_8001b17c(std::uint32_t a0);

}
