// SPDX-License-Identifier: GPL-3.0-or-later
#include "menu_table_sequence.hpp"

#include <cstring>

namespace am3d::exe {

const std::uint8_t kMenuInputScanSlotReleased[kMenuInputScanSlotBytes] = {0u, 0x41u, 0xffu,
                                                                          0xffu};
const std::uint8_t kMenuInputScanSlotUp[kMenuInputScanSlotBytes] = {0u, 0x41u, 0xefu, 0xffu};

void menu_table_fill_released_slots(std::uint8_t* table, std::size_t slot_count) {
    for (std::size_t slot = 0u; slot < slot_count; ++slot) {
        const std::size_t base = slot * kMenuInputScanSlotBytes;
        for (std::size_t i = 0u; i < kMenuInputScanSlotBytes; ++i) {
            table[base + i] = kMenuInputScanSlotReleased[i];
        }
    }
}

void menu_table_write_slot_at_cursor(std::uint8_t* table, std::uint32_t table_bytes,
                                     std::uint32_t table_cursor,
                                     const std::uint8_t slot[kMenuInputScanSlotBytes]) {
    if (table_cursor + kMenuInputScanSlotBytes > table_bytes) {
        return;
    }
    std::memcpy(table + table_cursor, slot, kMenuInputScanSlotBytes);
}

void MenuTableSequencer::reset() {
    step_index = 0u;
}

void MenuTableSequencer::apply_frame(std::uint8_t* table, std::uint32_t table_bytes,
                                     std::uint32_t table_cursor) {
    const std::uint8_t* pattern =
        (step_index & 1u) != 0u ? kMenuInputScanSlotUp : kMenuInputScanSlotReleased;
    menu_table_write_slot_at_cursor(table, table_bytes, table_cursor, pattern);
    step_index += 1u;
}

}  // namespace am3d::exe