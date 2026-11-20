// SPDX-License-Identifier: GPL-3.0-or-later
#include "alp1_pad_spawn.hpp"
#include "alp1_pad_spawn_fixture.hpp"

#include <cstdint>

int main() {
    const am3d::exe::Alp1PadSpawnParseResult result = am3d::exe::alp1_pad_spawn_disc_free_fixture();
    if (!result.ok) {
        return 1;
    }
    if (result.pad_index != 1u || result.x != am3d::exe::kAlp1PadSpawnDiscFreeGoldenX ||
        result.z != am3d::exe::kAlp1PadSpawnDiscFreeGoldenZ ||
        result.heading != am3d::exe::kAlp1PadSpawnDiscFreeGoldenHeading) {
        return 2;
    }
    const am3d::exe::Alp1PadSpawnParseResult short_buf = am3d::exe::parse_alp1_pad_spawn_from_bytes(
        {am3d::exe::kAlp1PadSpawnDiscFreeFixture.data(), 0x28u}, 1u);
    if (short_buf.ok) {
        return 3;
    }
    return 0;
}
