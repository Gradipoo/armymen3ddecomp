// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80065164.hpp"

#include <cstdint>

int main() {
    std::uint8_t record[0x200]{};
    std::uint8_t* cursor = record;
    std::uint32_t table_index = 3u;
    am3d::exe::MenuInputScanState scan{};
    scan.s7 = 2u;
    const bool again = am3d::exe::call_80065164(
        cursor, table_index, scan, 5u, nullptr);
    if (!again || table_index != 10u || scan.index != 1u || scan.s7 != 3u) {
        return 1;
    }
    if (cursor != record + 0x7cu) {
        return 2;
    }
    return 0;
}