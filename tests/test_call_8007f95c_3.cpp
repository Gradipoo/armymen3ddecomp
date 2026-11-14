// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007f95c_3.hpp"
int main() {
    unsigned d[8];
    for (int i = 0; i < 8; ++i) d[i] = 1;
    am3d::exe::call_8007f95c_3(d);
    for (int i = 0; i < 8; ++i) if (d[i] != 0) return 1;
    return 0;
}
