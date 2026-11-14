// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800957c8.hpp"

#include "call_800957e4.hpp"

namespace am3d::exe {

std::uint32_t call_800957c8(std::uint32_t& argument, std::uint32_t loaded,
                            std::uint32_t handler) {
    argument = loaded + 0xf0u;
    std::uint32_t base = 1;
    std::uint32_t next = 1;
    std::uint32_t flag = 0;
    std::uint32_t s0 = 0;
    (void)call_800957e4(base, next, flag, s0, 0x8009f510u, 0x80094f64u);
    return handler;
}

}
