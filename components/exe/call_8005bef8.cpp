// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8005bef8.hpp"
namespace am3d::exe {
std::uint32_t call_8005bef8(std::uint32_t flag) {
    if ((flag & 2u) == 0) {
        return 0;
    }
    // gap: jal 0x80081a00. That target is unnamed. This side is not taken when bit 1 is clear.
    return flag;
}
}
