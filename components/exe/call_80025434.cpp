// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80025434.hpp"

#include "call_8007d52c.hpp"

namespace am3d::exe {

void call_80025434(std::uint32_t addresses[5]) {
    addresses[0] = 0x800c8508u;
    addresses[1] = 0x800a01d4u;
    addresses[2] = 0x800a01dcu;
    addresses[3] = 0x800a01e4u;
    addresses[4] = 0x800a01ecu;
    for (int index = 0; index < 5; ++index) {
        std::uint32_t cleared = 1;
        call_8007d52c(addresses[index], cleared);
    }
    // gap: resume at 0x80025470. a0 is the unstated return from 0x8007d234 with a0 0.
}

}
