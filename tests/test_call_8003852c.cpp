// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8003852c.hpp"

#include <cstdint>

int main() {
    am3d::exe::Call8003852cArgs args{};
    args.a0 = 9;
    am3d::exe::call_8003852c(0, 3, -2, 0xa1b2c3d4u, 0, 0, args);
    if (args.invoke || args.a0 != 9) return 1;

    am3d::exe::call_8003852c(1, 3, -2, 0xa1b2c3d4u, 0, 7, args);
    if (!args.invoke || args.a0 != 3 || args.a1 != -2 || args.a2 != 0xa1b2c3d4u || args.a3 != 7) {
        return 2;
    }

    args.invoke = true;
    am3d::exe::call_8003852c(1, 3, -2, 0xa1b2c3d4u, 1, 7, args);
    if (args.invoke) return 3;

    am3d::exe::call_8003852c(1, 3, -2, 0xa1b2c3d4u, 0x80000000u, 4, args);
    if (!args.invoke || args.a3 != 4) return 4;
    return 0;
}
