// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80063b34.hpp"

int main() {
    if (am3d::exe::call_80063b34() != 0x800bfdbc) {
        return 1;
    }
    return 0;
}
