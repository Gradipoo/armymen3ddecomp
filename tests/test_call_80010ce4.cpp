// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80010ce4.hpp"

#include <array>
#include <cstdint>

int main() {
    std::array<std::uint8_t, am3d::exe::kCall80010ce4Bytes> object{};
    object.fill(0x5a);
    object[0x74] = 0;
    object[0x75] = 0;
    object[0x76] = 0;
    object[0x77] = 0;
    am3d::exe::Call80010ce4Args args{};
    args.a0 = 9;
    am3d::exe::call_80010ce4(object.data(), args);
    if (args.invoke || args.a0 != 9) return 1;
    for (std::size_t i = 0; i < object.size(); ++i) {
        const std::uint8_t expect = i >= 0x74 ? 0 : 0x5a;
        if (object[i] != expect) return 2;
    }

    object[0x6c] = 0xd4;
    object[0x6d] = 0xc3;
    object[0x6e] = 0xb2;
    object[0x6f] = 0xa1;
    object[0x70] = 0xfe;
    object[0x71] = 0xff;
    object[0x74] = 1;
    am3d::exe::call_80010ce4(object.data(), args);
    if (!args.invoke || args.a0 != 3 || args.a1 != -2 || args.a2 != 0xa1b2c3d4u ||
        args.a3 != 0 || args.stack_arg != 0) {
        return 3;
    }
    if (object[0x74] != 1 || object[0x72] != 0x5a) return 4;

    object[0x70] = 0x00;
    object[0x71] = 0x80;
    am3d::exe::call_80010ce4(object.data(), args);
    if (!args.invoke || args.a1 != -32768) return 5;
    return 0;
}
