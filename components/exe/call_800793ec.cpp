// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800793ec.hpp"
namespace am3d::exe {
std::uint32_t call_800793ec(std::uint32_t* words, std::uint32_t a1, std::uint32_t a2, std::uint32_t a3) {
    words[0] = a3 != 0u ? 1u : 0u;
    words[6] = 0xffffffffu;
    words[1] = 0;
    words[2] = a1;
    words[3] = a2;
    words[4] = 0;
    words[5] = 0;
    words[7] = 0;
    return 1;
}
}
