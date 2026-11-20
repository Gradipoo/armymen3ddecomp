// SPDX-License-Identifier: GPL-3.0-or-later
#include "alp1_pad_spawn.hpp"

#include <array>
#include <cstdint>

namespace {

// Minimal ALP1.PAD header (0x20 bytes) plus pad index 1 record measured from owner ALP1.PAD.
constexpr std::array<std::uint8_t, 0x30> kFixture = {
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x20, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x32, 0x00, 0xf9, 0xff, 0xe4, 0x04, 0x00, 0x00, 0x32, 0x00,
    0x10, 0x00, 0x32, 0x00, 0x30, 0x00,
};

constexpr std::int32_t kGoldenX = 50;
constexpr std::int32_t kGoldenZ = 1252;
constexpr std::int32_t kGoldenHeading = 50;

}  // namespace

int main() {
    const am3d::exe::Alp1PadSpawnParseResult result = am3d::exe::parse_alp1_pad_spawn_from_bytes(
        {kFixture.data(), kFixture.size()}, 1u);
    if (!result.ok) {
        return 1;
    }
    if (result.pad_index != 1u || result.x != kGoldenX || result.z != kGoldenZ ||
        result.heading != kGoldenHeading) {
        return 2;
    }
    const am3d::exe::Alp1PadSpawnParseResult short_buf = am3d::exe::parse_alp1_pad_spawn_from_bytes(
        {kFixture.data(), 0x28u}, 1u);
    if (short_buf.ok) {
        return 3;
    }
    return 0;
}