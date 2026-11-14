// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800793ec.hpp"
int main() {
    std::uint32_t words[8] = {9,9,9,9,9,9,9,9};
    if (am3d::exe::call_800793ec(words, 0x80073df8u, 0x8009f408u, 0) != 1u) return 1;
    if (words[0] || words[6] != 0xffffffffu || words[2] != 0x80073df8u) return 2;
    return 0;
}
