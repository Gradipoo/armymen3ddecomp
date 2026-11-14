// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80011cc0.hpp"
int main() {
    unsigned char buf[0x22] = {};
    buf[0x20] = 1;
    if (am3d::exe::call_80011cc0(buf) != 5u) return 1;
    if (buf[0x20] != 5 || buf[0x21] != 0) return 2;
    return 0;
}
