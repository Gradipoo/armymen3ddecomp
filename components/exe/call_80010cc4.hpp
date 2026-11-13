// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

// Block at 0x80010cc4. a0 becomes the object. a1 becomes the second argument.
void call_80010cc4(const std::uint8_t* object, std::uint32_t second);

}
