// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80064598.hpp"

int main() {
    if (am3d::exe::call_80064598(0x80025490u) != 0x80025490u) return 1;
    return 0;
}
