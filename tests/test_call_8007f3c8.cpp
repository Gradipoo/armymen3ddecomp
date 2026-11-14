// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007f3c8.hpp"
#include <cstdint>
int main() {
    std::int32_t first = 0;
    std::int32_t second = 0;
    am3d::exe::call_8007f3c8(first, second);
    if (first != -1 || second != -0x8000) return 1;
    return 0;
}
