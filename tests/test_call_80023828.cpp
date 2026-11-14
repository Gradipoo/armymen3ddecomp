// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80023828.hpp"

int main() {
    return am3d::exe::call_80023828() == 0x8002390c ? 0 : 1;
}
