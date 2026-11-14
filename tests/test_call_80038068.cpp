// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80038068.hpp"
int main() {
    const auto out = am3d::exe::call_80038068();
    if (out.counts[0] != 1 || out.counts[31] != 32) return 1;
    if (out.at_800aa294 != 0xffffffffu || out.at_800abe98 != 0xffffffffu) return 1;
    if (out.at_800abe9c != 0 || out.at_800d68b8 != 0) return 1;
    return 0;
}
