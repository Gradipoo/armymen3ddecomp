// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800381b0.hpp"

#include <cstdint>

int main() {
    if (am3d::exe::call_800381b0_slot(3) != 0x800a9fdcu) return 1;

    am3d::exe::Call800381b0Args args{};
    args.a0 = 9;
    std::uint32_t flag = 5;
    am3d::exe::call_800381b0(flag, 1, 0, 1, 0x10, 0x20, 3, -2, 0xa1b2c3d4u, args);
    if (args.invoke || args.a0 != 9 || flag != 5) return 2;

    flag = 0;
    am3d::exe::call_800381b0(flag, 0, 0, 1, 0x10, 0x20, 3, -2, 0xa1b2c3d4u, args);
    if (args.invoke || flag != 1) return 3;

    flag = 0;
    am3d::exe::call_800381b0(flag, 1, 2, 1, 0x10, 0x20, 3, -2, 0xa1b2c3d4u, args);
    if (args.invoke || flag != 1) return 4;

    flag = 0;
    am3d::exe::call_800381b0(flag, 1, 0xffffffffu, 0, 0x10, 0x20, 3, -2, 0xa1b2c3d4u, args);
    if (args.invoke || flag != 1) return 5;

    flag = 0;
    am3d::exe::call_800381b0(flag, 1, 0xffffffffu, 8, 0x1111u, 0x2222u, 3, -2, 0xa1b2c3d4u, args);
    if (!args.invoke || args.target != 0x1111u || args.a0 != 3 || args.a1 != -2 ||
        args.a2 != 0xa1b2c3d4u || args.a3 != 0x2222u || flag != 1) {
        return 6;
    }

    flag = 0;
    am3d::exe::call_800381b0(flag, 1, 0xfffffffeu, 8, 0x3333u, 0x44u, 3, -2, 0xa1b2c3d4u, args);
    if (!args.invoke || args.target != 0x3333u || args.a1 != -2 || args.a3 != 0x44u) return 7;
    return 0;
}
