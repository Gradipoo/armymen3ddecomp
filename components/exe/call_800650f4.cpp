// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800650f4.hpp"

#include "call_8006471c.hpp"
#include "call_8006518c.hpp"

namespace am3d::exe {

bool call_800650f4(std::uint8_t*& record, std::uint32_t stack_word_58,
                   MenuInputScanState& scan, std::uint32_t loop_limit) {
    record[0x0bu] = 0u;
    record[0x13u] = 0u;
    record[0x14u] = 0u;
    std::uint32_t masked = 0u;
    (void)call_8006471c(scan.index, stack_word_58, masked);
    record += 0x7cu;
    scan.s4 += 4u;
    scan.index += 1u;
    scan.fp <<= 1u;
    scan.s7 += 1u;
    scan.table_cursor += 4u;
    return menu_scan_should_loop(scan.s7, loop_limit);
}

}
