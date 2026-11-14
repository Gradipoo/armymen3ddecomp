// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

// Entry at 0x80079b24. a0 is 0x8009f388 or 0x8009f3a8. a1 is the object.
void call_80079b24(std::uint32_t a0);

}
