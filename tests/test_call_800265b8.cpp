// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800265b8.hpp"
#include <cstdint>
int main() {
    std::uint32_t slot = 1;
    am3d::exe::call_800265b8(slot);
    if (slot != 0u) return 1;
    return 0;
}
