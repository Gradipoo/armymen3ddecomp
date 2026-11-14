// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800957c8.hpp"

namespace am3d::exe {

std::uint32_t call_800957c8(std::uint32_t& argument, std::uint32_t loaded,
                            std::uint32_t handler) {
    argument = loaded + 0xf0u;
    // gap: jalr through handler. On this boot that word is 0. The return
    // address is 0x800957e4. The body is not in the executable.
    return handler;
}

}
