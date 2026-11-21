// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80064f14.hpp"

namespace am3d::exe {

MenuTableBytesResult call_80064f14(const std::uint8_t* table, std::uint32_t& index,
                                   std::uint32_t table_bytes) {
    MenuTableBytesResult result{};
    if (table == nullptr || index >= table_bytes) {
        return result;
    }
    const std::uint8_t first = table[index];
    if (first != 0u) {
        result.first_byte_branch = true;
        index += 1u;
        return result;
    }
    index += 1u;
    if (index >= table_bytes) {
        return result;
    }
    result.masked_a2 = table[index] & 0xffu;
    result.compare_0x41 = result.masked_a2 == 0x41u;
    index += 1u;
    // gap: fallthrough at 0x80064f34 to 0x80064f3c is not entered.
    // gap: taken path 0x80064f48 is not entered here.
    return result;
}

}