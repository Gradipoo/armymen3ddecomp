// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007a4e4.hpp"

int main() {
    if (am3d::exe::call_8007a4e4(0x8007c4a4u) != 0x800b5d78u) {
        return 1;
    }
    if (am3d::exe::call_8007a4e4(0x8005bf80u) != 0x800b3b68u) {
        return 1;
    }
    if (am3d::exe::call_8007a4e4(0) != 0) {
        return 1;
    }
    return 0;
}
