// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

struct Call80064758Outcome {
    bool masked_bits_zero;
    bool branch_to_647b8;
    bool copied_3c_to_1c;
    bool branch_to_647b0;
    bool stored_v1_at_1c;
    bool followed_64778_fallthrough;
    bool stored_1c_from_64798;
    bool or_sh_at_record_6;
    bool continues_at_647c4;
};

// Behavior reference: docs/research/re/call-80064758.md.
// record_bytes models lhu/sh at record offsets when the caller supplies the buffer.
// a1_low16 is the low 16 bits of the caller word at sp+0x58 (andi in call-8006471c.md).
std::uint32_t call_80064758(std::uint32_t halfword, std::uint32_t mask,
                            Call80064758Outcome* outcome = nullptr,
                            std::uint8_t* record_bytes = nullptr,
                            std::uint32_t a1_low16 = 0u);

} // namespace am3d::exe