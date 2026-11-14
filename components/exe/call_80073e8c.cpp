// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80073e8c.hpp"
#include "call_80073e70.hpp"
namespace am3d::exe {
std::uint32_t call_80073e8c(std::uint32_t a0, std::uint32_t a1, std::uint32_t old_word) {
    (void)a0;
    (void)(a1 & ~0x7ffu);
    call_80073e70();
    return old_word;
}
}
