// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

// Fourteenth entry at 0x8007f920. a0 is the destination. a1 is 0. a2 is 0xc.
void call_8007f920_14(std::uint8_t* dest);

}
