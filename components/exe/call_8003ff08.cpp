// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8003ff08.hpp"
namespace am3d::exe {
void call_8003ff08(std::uint32_t fourth) {
    // gap: jal 0x8003d874. a1 is a3. a2 is 0x400.
    (void)fourth;
}
}
