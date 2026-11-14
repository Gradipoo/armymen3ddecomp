// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800124cc.hpp"
namespace am3d::exe {
std::uint32_t call_800124cc(std::uint32_t* words) {
    static constexpr unsigned offsets[] = {
        0, 1, 2, 3, 4, 6, 7, 8, 9, 10, 11, 12, 13, 15, 16, 17, 18};
    for (unsigned index : offsets) {
        words[index] = 0;
    }
    return 0x800989a0u;
}
}
