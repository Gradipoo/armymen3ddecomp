// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8005c014.hpp"
namespace am3d::exe {
std::uint32_t call_8005c014(std::uint32_t word) {
    if ((word & 1u) == 0) {
        return 0;
    }
    return 0;
}
}
