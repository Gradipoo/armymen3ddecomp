// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include "alp1_pad_spawn.hpp"
#include "mission_movement_slice.hpp"

#include <array>
#include <cstdint>

namespace am3d::exe {

// Minimal ALP1.PAD header (0x20 bytes) plus pad index 1 record.
// Bytes match the measured owner record in docs/research/re/alp1-pad-spawn.md.
inline constexpr std::array<std::uint8_t, 0x30> kAlp1PadSpawnDiscFreeFixture = {
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x20, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x32, 0x00, 0xf9, 0xff, 0xe4, 0x04, 0x00, 0x00, 0x32, 0x00,
    0x10, 0x00, 0x32, 0x00, 0x30, 0x00,
};

// Low 16 bits of the pad index 1 record. See alp1-pad-spawn.md.
inline constexpr std::int32_t kAlp1PadSpawnDiscFreeGoldenX = 50;
inline constexpr std::int32_t kAlp1PadSpawnDiscFreeGoldenZ = 1252;
inline constexpr std::int32_t kAlp1PadSpawnDiscFreeGoldenHeading = 50;

inline Alp1PadSpawnParseResult alp1_pad_spawn_disc_free_fixture() {
    return parse_alp1_pad_spawn_from_bytes(
        {kAlp1PadSpawnDiscFreeFixture.data(), kAlp1PadSpawnDiscFreeFixture.size()}, 1u);
}

// Disc-free movement start decoded from kAlp1PadSpawnDiscFreeFixture.
// ok stays false only when that parse fails; then x/z/heading stay 0.
inline MissionMovementStartState mission_start_from_alp1_pad_fixture() {
    const Alp1PadSpawnParseResult parsed = alp1_pad_spawn_disc_free_fixture();
    MissionMovementStartState start{};
    if (!parsed.ok) {
        return start;
    }
    start.x = parsed.x;
    start.z = parsed.z;
    start.heading = parsed.heading;
    return start;
}

}  // namespace am3d::exe
