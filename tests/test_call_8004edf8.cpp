// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8004edf8.hpp"
#include <cstdint>
int main() {
    std::int16_t out[4] = {};
    am3d::exe::call_8004edf8(out);
    if (out[0] != -256 || out[1] != -120 || out[2] != 512 || out[3] != 240) return 1;
    return 0;
}
