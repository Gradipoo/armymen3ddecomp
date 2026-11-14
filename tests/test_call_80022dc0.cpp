// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80022dc0.hpp"
#include <cstdint>
int main() {
    std::uint32_t slot = 0;
    if (am3d::exe::call_80022dc0(slot) != 1u || slot != 1u) return 1;
    return 0;
}
