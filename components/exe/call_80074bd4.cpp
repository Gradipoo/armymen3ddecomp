// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80074bd4.hpp"
#include "call_80074360.hpp"
namespace am3d::exe {
void call_80074bd4(std::uint32_t flag) {
    if ((flag & 6u) != 6u) {
        call_80074360();
    }
    // gap: jal 0x8005bef8 at 0x80074c48. The callee is unnamed.
}
}
