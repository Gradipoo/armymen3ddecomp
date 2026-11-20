// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800650e0.hpp"

namespace am3d::exe {

bool call_800650e0(std::uint32_t complemented_input) {
    return (complemented_input & 0x40u) != 0u;
}

}
