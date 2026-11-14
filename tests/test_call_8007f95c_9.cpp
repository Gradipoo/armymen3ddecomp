// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007f95c_9.hpp"
int main() {
    unsigned d[10];
    for (int i = 0; i < 10; ++i) d[i] = 1;
    am3d::exe::call_8007f95c_9(d);
    for (int i = 0; i < 10; ++i) if (d[i] != 0) return 1;
    return 0;
}
