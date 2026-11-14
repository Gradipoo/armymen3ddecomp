// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800624cc_3.hpp"

int main() {
    int argument = 0;
    return am3d::exe::call_800624cc_3(0, &argument) == 0x80075198 && argument == 5 ? 0 : 1;
}
