// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80064758.hpp"

#include <cstring>

namespace am3d::exe {

namespace {

void clear_outcome(Call80064758Outcome& outcome) {
    outcome.masked_bits_zero = false;
    outcome.branch_to_647b8 = false;
    outcome.copied_3c_to_1c = false;
    outcome.branch_to_647b0 = false;
    outcome.stored_v1_at_1c = false;
    outcome.followed_64778_fallthrough = false;
    outcome.stored_1c_from_64798 = false;
    outcome.or_sh_at_record_6 = false;
    outcome.continues_at_647c4 = false;
}

std::uint16_t load_halfword(std::uint8_t* record_bytes, std::size_t offset) {
    std::uint16_t value = 0u;
    std::memcpy(&value, record_bytes + offset, sizeof(value));
    return value;
}

void store_halfword(std::uint8_t* record_bytes, std::size_t offset, std::uint16_t value) {
    std::memcpy(record_bytes + offset, &value, sizeof(value));
}

} // namespace

std::uint32_t call_80064758(std::uint32_t halfword, std::uint32_t mask,
                            Call80064758Outcome* outcome, std::uint8_t* record_bytes,
                            std::uint32_t a1_low16) {
    const std::uint32_t bits = halfword & mask;

    if (outcome != nullptr) {
        clear_outcome(*outcome);
    }

    if (bits == 0u) {
        if (outcome != nullptr) {
            outcome->masked_bits_zero = true;
            outcome->branch_to_647b8 = true;
            outcome->continues_at_647c4 = true;
        }
        if (record_bytes != nullptr) {
            const std::uint16_t at_3c = load_halfword(record_bytes, 0x3cu);
            store_halfword(record_bytes, 0x1cu, at_3c);
            if (outcome != nullptr) {
                outcome->copied_3c_to_1c = true;
            }
        }
        return bits;
    }

    if (record_bytes != nullptr) {
        const std::uint16_t at_1c = load_halfword(record_bytes, 0x1cu);
        const std::uint32_t v1 = static_cast<std::uint32_t>(at_1c) - a1_low16;
        if (static_cast<std::int32_t>(v1) > 0) {
            store_halfword(record_bytes, 0x1cu, static_cast<std::uint16_t>(v1));
            if (outcome != nullptr) {
                outcome->branch_to_647b0 = true;
                outcome->stored_v1_at_1c = true;
                outcome->continues_at_647c4 = true;
            }
        } else {
            const std::uint16_t at_5c = load_halfword(record_bytes, 0x5cu);
            const std::uint32_t v1_sum = v1 + static_cast<std::uint32_t>(at_5c);
            const std::uint16_t at_1c_store = static_cast<std::int32_t>(v1_sum) > 0
                                                    ? static_cast<std::uint16_t>(v1_sum)
                                                    : static_cast<std::uint16_t>(1u);
            store_halfword(record_bytes, 0x1cu, at_1c_store);

            const std::uint16_t at_6 = load_halfword(record_bytes, 0x6u);
            const std::uint16_t at_6_or =
                static_cast<std::uint16_t>(at_6 | static_cast<std::uint16_t>(mask & 0xffffu));
            store_halfword(record_bytes, 0x6u, at_6_or);

            if (outcome != nullptr) {
                outcome->followed_64778_fallthrough = true;
                outcome->stored_1c_from_64798 = true;
                outcome->or_sh_at_record_6 = true;
                outcome->continues_at_647c4 = true;
            }
        }
    }

    return bits;
}

} // namespace am3d::exe