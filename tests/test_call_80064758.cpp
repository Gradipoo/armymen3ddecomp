// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80064758.hpp"

#include <array>
#include <cstdint>

int main() {
    if (am3d::exe::call_80064758(0u, 1u) != 0u) {
        return 1;
    }
    if (am3d::exe::call_80064758(1u, 1u) != 1u) {
        return 2;
    }
    if (am3d::exe::call_80064758(0x100u, 1u) != 0u) {
        return 3;
    }
    if (am3d::exe::call_80064758(0xffffu, 1u) != 1u) {
        return 4;
    }

    am3d::exe::Call80064758Outcome outcome{};
    std::array<std::uint8_t, 0x40u> record{};
    record[0x3cu] = 0xabu;
    record[0x3du] = 0xcdu;
    record[0x1cu] = 0xffu;
    record[0x1du] = 0xffu;
    if (am3d::exe::call_80064758(0u, 1u, &outcome, record.data()) != 0u) {
        return 5;
    }
    if (!outcome.masked_bits_zero || !outcome.branch_to_647b8 ||
        !outcome.copied_3c_to_1c || !outcome.continues_at_647c4 ||
        outcome.branch_to_647b0 || outcome.stored_v1_at_1c) {
        return 6;
    }
    if (record[0x1cu] != 0xabu || record[0x1du] != 0xcdu) {
        return 7;
    }

    outcome = {};
    record[0x1cu] = 0x10u;
    record[0x1du] = 0u;
    if (am3d::exe::call_80064758(1u, 1u, &outcome, record.data(), 5u) != 1u) {
        return 8;
    }
    if (outcome.masked_bits_zero || outcome.branch_to_647b8 ||
        !outcome.branch_to_647b0 || !outcome.stored_v1_at_1c ||
        !outcome.continues_at_647c4 || outcome.copied_3c_to_1c) {
        return 9;
    }
    if (record[0x1cu] != 0x0bu || record[0x1du] != 0u) {
        return 10;
    }

    outcome = {};
    if (am3d::exe::call_80064758(0u, 1u, &outcome, nullptr) != 0u) {
        return 11;
    }
    if (!outcome.masked_bits_zero || !outcome.branch_to_647b8 ||
        !outcome.continues_at_647c4 || outcome.copied_3c_to_1c) {
        return 12;
    }

    outcome = {};
    if (am3d::exe::call_80064758(3u, 1u, &outcome, nullptr, 1u) != 1u) {
        return 13;
    }
    if (outcome.branch_to_647b8 || outcome.branch_to_647b0 ||
        outcome.stored_v1_at_1c) {
        return 14;
    }

    outcome = {};
    std::array<std::uint8_t, 0x5eu> record_wide{};
    record_wide[0x1cu] = 3u;
    record_wide[0x1du] = 0u;
    record_wide[0x5cu] = 2u;
    record_wide[0x5du] = 0u;
    record_wide[0x6u] = 0x80u;
    record_wide[0x7u] = 0u;
    if (am3d::exe::call_80064758(1u, 1u, &outcome, record_wide.data(), 5u) != 1u) {
        return 15;
    }
    if (outcome.masked_bits_zero || outcome.branch_to_647b8 || outcome.copied_3c_to_1c ||
        outcome.branch_to_647b0 || outcome.stored_v1_at_1c ||
        !outcome.followed_64778_fallthrough || !outcome.stored_1c_from_64798 ||
        !outcome.or_sh_at_record_6 || !outcome.continues_at_647c4) {
        return 16;
    }
    if (record_wide[0x1cu] != 1u || record_wide[0x1du] != 0u) {
        return 17;
    }
    if (record_wide[0x6u] != 0x81u || record_wide[0x7u] != 0u) {
        return 18;
    }

    return 0;
}