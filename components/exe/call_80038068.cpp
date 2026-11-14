// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80038068.hpp"
namespace am3d::exe {
Call80038068Result call_80038068() {
    Call80038068Result out{};
    for (std::uint32_t index = 0; index < 32; index += 1) {
        out.counts[index] = index + 1;
    }
    out.at_800aa294 = 0xffffffffu;
    out.at_800abe98 = 0xffffffffu;
    out.at_800abe9c = 0;
    out.at_800d68b8 = 0;
    return out;
}
}
