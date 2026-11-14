// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80036278.hpp"
namespace am3d::exe {
void call_80036278(const std::uint8_t* object) {
    // gap: jal 0x80018b64. a0 is the object plus 0x34.
    (void)object;
}
}
