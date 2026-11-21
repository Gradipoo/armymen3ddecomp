// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstddef>
#include <cstdint>

namespace am3d::exe {

constexpr std::size_t kMenuInputScanSlotBytes = 4u;

// Four-byte slot patterns from tests/test_menu_input_scan.cpp (0x41 second byte).
extern const std::uint8_t kMenuInputScanSlotReleased[kMenuInputScanSlotBytes];
extern const std::uint8_t kMenuInputScanSlotUp[kMenuInputScanSlotBytes];

// Fill every 4-byte table slot with the released pattern.
void menu_table_fill_released_slots(std::uint8_t* table, std::size_t slot_count);

// Overwrite one slot at byte offset table_cursor when it fits in table_bytes.
void menu_table_write_slot_at_cursor(std::uint8_t* table, std::uint32_t table_bytes,
                                     std::uint32_t table_cursor,
                                     const std::uint8_t slot[kMenuInputScanSlotBytes]);

// Disc-free script: even frames patch released, odd frames patch up at scan.table_cursor.
// Mimics OPTIONS and NEW GAME halfword paths without retail table dumps.
// Behavior notes: docs/research/re/menu-table-sequence.md.
struct MenuTableSequencer {
    std::uint32_t step_index = 0u;

    void apply_frame(std::uint8_t* table, std::uint32_t table_bytes,
                     std::uint32_t table_cursor);
    void reset();
};

}  // namespace am3d::exe