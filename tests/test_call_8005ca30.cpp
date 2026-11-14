// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8005ca30.hpp"
int main() {
    const std::uint8_t legal[] = "legal.bg";
    const std::uint8_t mission[] = "\\mission.ini";
    if (am3d::exe::call_8005ca30(legal) != legal) return 1;
    if (am3d::exe::call_8005ca30(mission) != mission) return 2;
    return 0;
}
