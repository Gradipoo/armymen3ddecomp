// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8002134c.hpp"
#include <cstring>
namespace am3d::exe {
std::uint8_t* call_8002134c(std::uint8_t* object, std::uint32_t value) {
    std::memcpy(object, &value, 4);
    // gap: jal 0x8007f598. a0 is the object plus 4. a1 is 0x8009f270. a2 is 0xa0.
    return object;
}
}
