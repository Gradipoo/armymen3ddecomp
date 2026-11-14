// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800254fc.hpp"

int main() {
    std::uint32_t a0 = 0;
    std::uint32_t s2 = 0x80080000u;
    std::uint32_t cleared = 9;
    am3d::exe::call_800254fc(a0, s2, cleared);
    if (a0 != 2 || s2 != 0x8009f820u || cleared != 0) return 1;
    return 0;
}
