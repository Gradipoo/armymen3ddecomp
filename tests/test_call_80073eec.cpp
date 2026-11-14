// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80073eec.hpp"
int main() {
    return am3d::exe::call_80073eec(0, 0x800u, 0) == 0x800u ? 0 : 1;
}
