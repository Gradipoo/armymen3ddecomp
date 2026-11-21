// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800650f4.hpp"

#include <array>
#include <cstdint>

int main() {
    std::array<std::uint8_t, 0x100u> bytes{};
    bytes[0x0bu] = 0x80u;
    bytes[0x13u] = 0xffu;
    bytes[0x14u] = 0xffu;
    std::uint8_t* record = bytes.data();
    am3d::exe::MenuInputScanState scan{};
    scan.index = 2u;
    scan.fp = 1u;
    if (!am3d::exe::call_800650f4(record, 0xabcdu, scan, 4u)) {
        return 1;
    }
    if (bytes[0x0bu] != 0u || bytes[0x13u] != 0u || bytes[0x14u] != 0u) {
        return 2;
    }
    if (record != bytes.data() + 0x7cu) {
        return 3;
    }
    if (scan.index != 3u || scan.s4 != 4u || scan.s7 != 1u || scan.fp != 2u ||
        scan.table_cursor != 4u) {
        return 4;
    }
    return 0;
}
