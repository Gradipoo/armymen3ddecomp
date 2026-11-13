// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8002fb9c.hpp"

#include <array>
#include <cstdint>

int main() {
    std::array<std::uint8_t, am3d::exe::kCall8002fb9cBytes> object{};
    std::array<std::uint8_t, am3d::exe::kCall8002fb9cTableBytes> table{};
    object.fill(0x11);
    for (std::size_t i = 0; i < table.size(); ++i) {
        table[i] = static_cast<std::uint8_t>(0x40 + i);
    }
    am3d::exe::call_8002fb9c(object.data(), 0x22u, table.data());
    for (std::size_t i = 0; i < object.size(); ++i) {
        std::uint8_t expect = 0x11;
        if (i < 4) expect = 0;
        if (i >= 4 && i < 0x24) expect = table[i - 4];
        if (i >= 0x24 && i < 0x28) expect = 0;
        if (i == 0x34) expect = 0x1;
        if (i == 0x35) expect = 0xff;
        if (i == 0x36 || i == 0x37) expect = 0;
        if (object[i] != expect) return 1;
    }
    return 0;
}
