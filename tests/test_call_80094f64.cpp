// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80094f64.hpp"

int main() {
    if (am3d::exe::call_80094f64(0x80064598u) != 0x80064598u) return 1;
    return 0;
}
