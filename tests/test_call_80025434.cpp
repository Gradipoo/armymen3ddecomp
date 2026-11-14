// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80025434.hpp"

int main() {
    std::uint32_t addresses[5] = {};
    am3d::exe::call_80025434(addresses);
    if (addresses[0] != 0x800c8508u) return 1;
    if (addresses[1] != 0x800a01d4u) return 2;
    if (addresses[2] != 0x800a01dcu) return 3;
    if (addresses[3] != 0x800a01e4u) return 4;
    if (addresses[4] != 0x800a01ecu) return 5;
    return 0;
}
