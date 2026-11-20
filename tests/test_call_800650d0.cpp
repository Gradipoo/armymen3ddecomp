// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800650d0.hpp"

#include <array>
#include <cstdint>

int main() {
    std::array<std::uint8_t, 0x100u> bytes{};
    std::uint8_t* record = bytes.data();
    am3d::exe::MenuInputScanState scan{};
    scan.index = 0u;
    if (am3d::exe::call_800650d0(record, 0u, 0xffffu, scan, 0u)) {
        return 1;
    }
    if (record != bytes.data()) {
        return 2;
    }
    if (!am3d::exe::call_800650d0(record, 0x10u, 0xabcdu, scan, 4u)) {
        return 3;
    }
    if (bytes[0x0bu] != 0x80u || bytes[0x13u] != 0u || bytes[0x14u] != 0u) {
        return 4;
    }
    if (record != bytes.data() + 0x7cu) {
        return 5;
    }
    if (scan.index != 1u || scan.s4 != 4u || scan.s7 != 1u || scan.table_cursor != 4u) {
        return 6;
    }
    return 0;
}