// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80065638.hpp"
int main() {
    if (am3d::exe::call_80065638(0) != 0u) return 1;
    if (am3d::exe::call_80065638(4) != 1u) return 2;
    return 0;
}
