// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80065168.hpp"

#include <array>
#include <cstdint>

int main() {
    std::array<std::uint8_t, 0x100u> bytes{};
    std::uint8_t* record = bytes.data();
    am3d::exe::MenuInputScanState scan{};
    scan.s4 = 8u;
    scan.index = 2u;
    scan.fp = 0x10u;
    scan.s7 = 1u;
    scan.table_cursor = 0u;
    std::uint32_t sp28 = 12u;
    if (!am3d::exe::call_80065168(record, scan, 8u, &sp28)) {
        return 1;
    }
    if (record != bytes.data() + 0x7cu || scan.s4 != 12u || scan.index != 3u ||
        scan.fp != 0x20u || scan.s7 != 2u || scan.table_cursor != 4u ||
        sp28 != 16u) {
        return 2;
    }
    if (am3d::exe::call_80065168(record, scan, 2u, &sp28)) {
        return 3;
    }
    return 0;
}