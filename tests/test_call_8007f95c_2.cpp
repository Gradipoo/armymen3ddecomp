// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007f95c_2.hpp"

int main() {
    unsigned dest[8];
    for (int i = 0; i < 8; ++i) {
        dest[i] = 1;
    }
    am3d::exe::call_8007f95c_2(dest);
    for (int i = 0; i < 8; ++i) {
        if (dest[i] != 0) {
            return 1;
        }
    }
    return 0;
}
