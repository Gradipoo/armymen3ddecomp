// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80063b08.hpp"

int main() {
    if (am3d::exe::call_80063b08_a0() != 0x800dd6e8u) {
        return 1;
    }
    return 0;
}
