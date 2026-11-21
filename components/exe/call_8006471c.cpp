// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8006471c.hpp"

#include "call_80064758.hpp"

#include <cstring>

namespace am3d::exe {

namespace {

std::uint16_t load_halfword_at_1c(const std::uint8_t* record_bytes) {
    std::uint16_t value = 0u;
    std::memcpy(&value, record_bytes + 0x1cu, sizeof(value));
    return value;
}

std::uint16_t load_halfword_at_4(const std::uint8_t* record_bytes) {
    std::uint16_t value = 0u;
    std::memcpy(&value, record_bytes + 4u, sizeof(value));
    return value;
}

std::uint16_t reload_halfword_1c(const std::uint8_t* record_bytes,
                                 const std::uint16_t* inject_halfword_1c) {
    if (record_bytes != nullptr) {
        return load_halfword_at_1c(record_bytes);
    }
    if (inject_halfword_1c != nullptr) {
        return *inject_halfword_1c;
    }
    return 0u;
}

} // namespace

std::uint32_t call_8006471c(std::uint32_t index, std::uint32_t bits, std::uint32_t& masked,
                            Call8006471cOutcome* outcome, const std::uint8_t* record_bytes,
                            const std::uint16_t* inject_halfword_1c,
                            const std::uint16_t* inject_halfword_4) {
    const std::uint32_t record = 0x800dd748u + index * 124u;
    masked = bits & 0xffffu;

    if (outcome != nullptr) {
        outcome->halfword_at_1c_stated = false;
        outcome->branch_to_647c4 = false;
        outcome->completed_647c4_loop = false;
        outcome->returned_to_caller = false;
        outcome->fell_through_64758 = false;
        outcome->fallthrough_bits = 0u;
    }

    const std::uint16_t* halfword_1c_ptr = nullptr;
    std::uint16_t halfword_1c_from_record = 0u;
    if (record_bytes != nullptr) {
        halfword_1c_from_record = load_halfword_at_1c(record_bytes);
        halfword_1c_ptr = &halfword_1c_from_record;
    } else if (inject_halfword_1c != nullptr) {
        halfword_1c_ptr = inject_halfword_1c;
    }

    if (halfword_1c_ptr == nullptr) {
        return record;
    }

    if (outcome != nullptr) {
        outcome->halfword_at_1c_stated = true;
    }

    const auto fallthrough_64758 = [&](std::uint32_t a2_mask) -> bool {
        std::uint16_t halfword_at_4 = 0u;
        if (record_bytes != nullptr) {
            halfword_at_4 = load_halfword_at_4(record_bytes);
        } else if (inject_halfword_4 != nullptr) {
            halfword_at_4 = *inject_halfword_4;
        } else {
            // gap: lhu at record+4 unstated without record_bytes or inject.
            return false;
        }

        std::uint8_t* record_mut =
            record_bytes != nullptr ? const_cast<std::uint8_t*>(record_bytes) : nullptr;
        Call80064758Outcome outcome_64758{};
        const std::uint32_t masked_bits = call_80064758(halfword_at_4, a2_mask, &outcome_64758,
                                                        record_mut, bits & 0xffffu);
        if (outcome != nullptr) {
            outcome->fell_through_64758 = true;
            outcome->fallthrough_bits = masked_bits;
        }
        return outcome_64758.continues_at_647c4;
    };

    const auto run_647c4_loop = [&](std::uint32_t t1, std::uint32_t a2_reg) -> std::uint32_t {
        for (;;) {
            t1 += 1u;
            a2_reg <<= 1u;
            if (t1 < 0x10u) {
                const std::uint16_t halfword_1c_loop =
                    reload_halfword_1c(record_bytes, inject_halfword_1c);
                if (halfword_1c_loop != 0u) {
                    if (fallthrough_64758(a2_reg)) {
                        continue;
                    }
                    return record;
                }
                continue;
            }
            if (outcome != nullptr) {
                outcome->completed_647c4_loop = true;
                outcome->returned_to_caller = true;
            }
            return record;
        }
    };

    if (*halfword_1c_ptr == 0u) {
        if (outcome != nullptr) {
            outcome->branch_to_647c4 = true;
        }
        return run_647c4_loop(0u, 1u);
    }

    if (fallthrough_64758(1u)) {
        return run_647c4_loop(0u, 1u);
    }
    return record;
}

} // namespace am3d::exe