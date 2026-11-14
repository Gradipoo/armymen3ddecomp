// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80010f5c.hpp"

#include "table_8009f0b4.hpp"

#include <array>
#include <cstdint>

int main() {
    std::array<std::uint8_t, am3d::exe::kCall80010f5cBytes> object{};
    object.fill(0x11);
    am3d::exe::call_80010f5c(object.data(), 0x22u);
    for (std::size_t i = 0; i < object.size(); ++i) {
        std::uint8_t expect = 0x11;
        if (i < 4 || (i >= 0x24 && i < 0x28) || i == 0x36 || i == 0x37) expect = 0;
        if (i >= 4 && i < 0x24) expect = am3d::exe::kTable8009f0b4[i - 4];
        if (i == 0x34) expect = 1;
        if (i == 0x35) expect = 0xff;
        if (i == 0x68) expect = 0x5c;
        if (i == 0x69) expect = 0x00;
        if (i == 0x6a) expect = 0x0c;
        if (i == 0x6b) expect = 0x80;
        if (object[i] != expect) return 1;
    }
    return 0;
}
