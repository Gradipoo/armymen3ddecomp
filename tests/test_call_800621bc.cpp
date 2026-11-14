// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800621bc.hpp"

#include <cstdint>

int main() {
    std::uint32_t a = 0;
    std::uint32_t b = 0;
    am3d::exe::call_800621bc(&a, &b);
    if (a != 0xffffffffu || b != 0xffffffffu) {
        return 1;
    }
    return 0;
}
