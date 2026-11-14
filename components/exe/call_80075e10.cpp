// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80075e10.hpp"
namespace am3d::exe {
std::uint32_t call_80075e10(std::uint32_t flag) {
    if ((flag & 1u) == 0) {
        return 0;
    }
    return flag;
}
}
