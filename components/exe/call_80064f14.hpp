// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

struct MenuTableBytesResult {
    std::uint8_t masked_a2;
    bool first_byte_branch;
    bool compare_0x41;
};

// Behavior references: docs/research/re/call-80064f14.md and call-80064f24.md.
// table is a host buffer. index is the s1 cursor (byte offset into table).
// Stops at the unknown beq fallthrough at 0x80064f34.
MenuTableBytesResult call_80064f14(const std::uint8_t* table, std::uint32_t& index,
                                   std::uint32_t table_bytes);

}