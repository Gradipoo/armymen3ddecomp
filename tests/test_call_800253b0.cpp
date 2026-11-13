// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800253b0.hpp"

using namespace am3d::exe;

int main() {
    Call800253b0Args calls[5]{};
    call_800253b0(calls);
    if (calls[0].a0 != 0x800ccd18u || calls[0].a1 != 0x900u) return 1;
    if (calls[1].a0 != 0x800cf118u || calls[1].a1 != 0x900u) return 2;
    if (calls[2].a0 != 0 || calls[2].a1 != 1) return 3;
    if (calls[3].a0 != 0 || calls[3].a1 != 1) return 4;
    if (calls[4].a0 != 0x100u || calls[4].a1 != 0x78u) return 5;
    return 0;
}
