// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800901fc.hpp"
#include <cstdint>
int main() {
    std::uint32_t second = 1;
    std::uint32_t third = 1;
    am3d::exe::call_800901fc(second, third);
    if (second != 0x3fu || third != 0) return 1;
    return 0;
}
