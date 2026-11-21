// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80065144.hpp"

#include <cstdint>

int main() {
    const auto four = am3d::exe::call_80065144(4u);
    if (!four.compare_eq_four) {
        return 1;
    }
    const auto zero = am3d::exe::call_80065144(0u);
    if (zero.compare_eq_four) {
        return 2;
    }
    return 0;
}