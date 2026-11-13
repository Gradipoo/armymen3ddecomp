// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007e150.hpp"

using namespace am3d::exe;

int main() {
    std::uint32_t a0 = 0x200u;
    call_8007e150(a0);
    if (a0 != 0x200u) return 1;
    return 0;
}
