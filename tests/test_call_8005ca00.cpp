// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8005ca00.hpp"
int main() {
    const std::uint8_t legal[] = "legal.bg";
    const std::uint8_t mission[] = "\\mission.ini";
    if (am3d::exe::call_8005ca00(legal) != legal) return 1;
    if (am3d::exe::call_8005ca00(mission) != mission) return 2;
    if (am3d::exe::toupper('l') != 'L') return 3;
    if (am3d::exe::toupper('\\') != '\\') return 4;
    return 0;
}
