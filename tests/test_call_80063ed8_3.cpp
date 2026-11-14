// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80063ed8_3.hpp"
int main() {
    unsigned w = 0xc0b;
    am3d::exe::call_80063ed8_3(&w);
    return w == 0 ? 0 : 1;
}
