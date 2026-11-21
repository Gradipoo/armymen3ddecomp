// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstddef>
#include <cstdint>
#include <filesystem>

namespace am3d::exe {

// Player spawn pad index 1 (TXT: PAD ambusha 1).
// Record +0x0/+0x4/+0x8 low words → x/z/heading. See docs/research/re/alp1-pad-spawn.md.
struct Alp1PadSpawnParseResult {
    bool ok = false;
    std::int32_t x = 0;
    std::int32_t z = 0;
    std::int32_t heading = 0;
    std::uint32_t pad_index = 0u;
};

struct Alp1PadBytes {
    const std::uint8_t* data = nullptr;
    std::size_t size = 0u;
};

// Parses one pad record. Default pad_index is 1 (prototype player spawn).
Alp1PadSpawnParseResult parse_alp1_pad_spawn_from_bytes(Alp1PadBytes bytes,
                                                          std::uint32_t pad_index = 1u);

// Reads DATA/ALP1.PAD under disc_root (e.g. build/disc).
Alp1PadSpawnParseResult load_alp1_pad_spawn_from_disc_root(
    const std::filesystem::path& disc_root, std::uint32_t pad_index = 1u);

}  // namespace am3d::exe