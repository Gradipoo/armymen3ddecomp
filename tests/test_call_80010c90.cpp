// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80010c90.hpp"

#include <array>
#include <cstdint>

int main() {
    std::array<std::uint8_t, am3d::exe::kCall80010c90Bytes> object{};
    object.fill(0x11);
    object[0x74] = 0;
    object[0x75] = 0;
    object[0x76] = 0;
    object[0x77] = 0;
    am3d::exe::call_80010c90(object.data(), 0x22);
    for (std::size_t i = 0; i < object.size(); ++i) {
        std::uint8_t expect = 0x11;
        if (i == 0x68) expect = 0x5c;
        if (i == 0x69) expect = 0x00;
        if (i == 0x6a) expect = 0x0c;
        if (i == 0x6b) expect = 0x80;
        if (i >= 0x74) expect = 0;
        if (object[i] != expect) return 1;
    }

    object[0x74] = 1;
    am3d::exe::call_80010c90(object.data(), 0x33);
    if (object[0x68] != 0x68 || object[0x69] != 0xe7 || object[0x6a] != 0x0b || object[0x6b] != 0x80) {
        return 2;
    }
    if (object[0x74] != 1) return 3;
    return 0;
}
