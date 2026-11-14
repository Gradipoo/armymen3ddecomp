// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8003f770.hpp"
int main() {
    std::uint32_t low=1, high=1;
    am3d::exe::call_8003f770(low, high);
    if (low||high) return 1;
    return 0;
}
