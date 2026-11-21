// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80065164.hpp"

#include "call_8006518c.hpp"  // menu_scan_should_loop

namespace am3d::exe {

bool call_80065164(std::uint8_t*& record, std::uint32_t& menu_table_index,
                   MenuInputScanState& scan, std::uint32_t stack_word_1c,
                   std::uint32_t* stack_word_28) {
    menu_table_index += 7u;
    record += 0x7cu;
    scan.s4 += 4u;
    scan.index += 1u;
    scan.fp <<= 1u;
    scan.s7 += 1u;
    scan.table_cursor += 4u;
    if (stack_word_28 != nullptr) {
        *stack_word_28 += 4u;
    }
    return menu_scan_should_loop(scan.s7, stack_word_1c);
}

}  // namespace am3d::exe