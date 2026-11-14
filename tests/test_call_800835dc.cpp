// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800835dc.hpp"
#include <cstdint>
int main() {
    std::uint8_t port = 1;
    std::uint8_t index = 0;
    std::uint32_t first = 0;
    std::uint32_t second = 0;
    am3d::exe::call_800835dc(port, index, first, second);
    if (port != 0 || index != 0x80) return 1;
    if (first != 0x2102843u || second != 0x1325u) return 1;
    return 0;
}
