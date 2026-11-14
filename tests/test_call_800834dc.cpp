// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800834dc.hpp"
#include <cstdint>
int main() {
    std::uint8_t port = 1;
    std::uint8_t index = 0;
    std::uint32_t first = 0;
    std::uint32_t second = 0;
    am3d::exe::call_800834dc(port, index, first, second);
    if (port != 0 || index != 0x80) return 1;
    if (first != 0x20943u || second != 0x1323u) return 1;
    return 0;
}
