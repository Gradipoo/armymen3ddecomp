// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80079b24.hpp"

int main() {
    if (am3d::exe::call_80079b24(0x8009f388u) != 0) return 1;
    if (am3d::exe::call_80079b24(0x8009f3a8u) != 0) return 2;
    return 0;
}
