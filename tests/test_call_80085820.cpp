// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80085820.hpp"
int main() {
    if (am3d::exe::call_80085820(0) != 0u) return 1;
    return 0;
}
