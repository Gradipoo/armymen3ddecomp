// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8006471c.hpp"

#include <array>
#include <cstdint>

int main() {
    std::uint32_t masked = 0u;
    am3d::exe::Call8006471cOutcome outcome{};

    if (am3d::exe::call_8006471c(0u, 0x12345678u, masked) != 0x800dd748u) {
        return 1;
    }
    if (masked != 0x5678u) {
        return 2;
    }

    std::array<std::uint8_t, 0x40u> record{};
    record[0x1cu] = 0u;
    record[0x1du] = 0u;
    record[4u] = 1u;
    if (!am3d::exe::call_8006471c(0u, 0xffffu, masked, &outcome, record.data())) {
        return 3;
    }
    if (!outcome.halfword_at_1c_stated || !outcome.branch_to_647c4 ||
        outcome.fell_through_64758) {
        return 4;
    }

    record[0x1cu] = 3u;
    record[4u] = 1u;
    outcome = {};
    (void)am3d::exe::call_8006471c(0u, 0u, masked, &outcome, record.data());
    if (!outcome.halfword_at_1c_stated || outcome.branch_to_647c4 ||
        !outcome.fell_through_64758 || outcome.fallthrough_bits != 1u) {
        return 5;
    }

    const std::uint16_t inject_1c = 2u;
    const std::uint16_t inject_4 = 0u;
    outcome = {};
    (void)am3d::exe::call_8006471c(0u, 0u, masked, &outcome, nullptr, &inject_1c, &inject_4);
    if (!outcome.halfword_at_1c_stated || outcome.branch_to_647c4 ||
        !outcome.fell_through_64758 || outcome.fallthrough_bits != 0u) {
        return 6;
    }

    return 0;
}