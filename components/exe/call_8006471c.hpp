// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

struct Call8006471cOutcome {
    bool halfword_at_1c_stated;
    bool branch_to_647c4;
    bool completed_647c4_loop;
    bool returned_to_caller;
    bool fell_through_64758;
    std::uint32_t fallthrough_bits;
};

// Behavior reference: docs/research/re/call-8006471c.md.
// record_bytes models lhu at record+0x1c and record+4 from the caller buffer.
// inject_halfword_* supplies the compare when record_bytes is null (ctests only).
std::uint32_t call_8006471c(std::uint32_t index, std::uint32_t bits, std::uint32_t& masked,
                            Call8006471cOutcome* outcome = nullptr,
                            const std::uint8_t* record_bytes = nullptr,
                            const std::uint16_t* inject_halfword_1c = nullptr,
                            const std::uint16_t* inject_halfword_4 = nullptr);

} // namespace am3d::exe