// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8005c9b0.hpp"
#include <cstring>
int main() {
    const std::uint8_t legal[] = "legal.bg";
    const std::uint8_t mission[] = "\\mission.ini";
    std::uint8_t dest[16] = {};
    if (am3d::exe::call_8005c9b0(legal, dest) != 8) return 1;
    if (std::strcmp(reinterpret_cast<char*>(dest), "legal.bg") != 0) return 2;
    if (am3d::exe::call_8005c9b0(mission, dest) != 12) return 3;
    if (std::strcmp(reinterpret_cast<char*>(dest), "\\mission.ini") != 0) return 4;
    return 0;
}
