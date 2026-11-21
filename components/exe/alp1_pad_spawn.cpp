// SPDX-License-Identifier: GPL-3.0-or-later
#include "alp1_pad_spawn.hpp"

#include "disc_data_file_read.hpp"
#include "mission_movement_slice.hpp"

#include <cstdint>
#include <vector>

namespace am3d::exe {
namespace {

constexpr std::size_t kAlp1PadHeaderBytes = 0x20u;
constexpr std::size_t kAlp1PadRecordStride = 0x10u;
// Measured owner size. See docs/research/re/alp1-pad-spawn.md.
constexpr std::size_t kAlp1PadMeasuredBytes = 0x2000u;

std::int32_t low_u16(std::uint32_t word) {
    return static_cast<std::int32_t>(word & 0xffffu);
}

std::uint32_t read_le32(const std::uint8_t* data, std::size_t offset) {
    return static_cast<std::uint32_t>(data[offset]) |
           (static_cast<std::uint32_t>(data[offset + 1u]) << 8u) |
           (static_cast<std::uint32_t>(data[offset + 2u]) << 16u) |
           (static_cast<std::uint32_t>(data[offset + 3u]) << 24u);
}

}  // namespace

Alp1PadSpawnParseResult parse_alp1_pad_spawn_from_bytes(Alp1PadBytes bytes,
                                                          std::uint32_t pad_index) {
    Alp1PadSpawnParseResult result{};
    result.pad_index = pad_index;
    if (bytes.data == nullptr || pad_index == 0u) {
        return result;
    }
    const std::size_t record_end =
        kAlp1PadHeaderBytes + static_cast<std::size_t>(pad_index) * kAlp1PadRecordStride;
    if (bytes.size < record_end) {
        return result;
    }
    const std::size_t record_off =
        kAlp1PadHeaderBytes + static_cast<std::size_t>(pad_index - 1u) * kAlp1PadRecordStride;
    const std::uint32_t word0 = read_le32(bytes.data, record_off);
    const std::uint32_t word1 = read_le32(bytes.data, record_off + 4u);
    const std::uint32_t word2 = read_le32(bytes.data, record_off + 8u);
    result.x = low_u16(word0);
    result.z = low_u16(word1);
    result.heading = low_u16(word2);
    result.ok = true;
    return result;
}

Alp1PadSpawnParseResult load_alp1_pad_spawn_from_disc_root(
    const std::filesystem::path& disc_root, std::uint32_t pad_index) {
    const std::filesystem::path resolved = disc_root / MissionSliceDeclaration::kPadPath;
    std::vector<std::uint8_t> buffer(kAlp1PadMeasuredBytes);
    const am3d::platform::DiscDataFileReadResult read = am3d::platform::read_disc_data_file(
        resolved, kAlp1PadMeasuredBytes, buffer.data());
    if (!read.ok || read.truncated || read.bytes_read == 0u) {
        return {};
    }
    buffer.resize(read.bytes_read);
    return parse_alp1_pad_spawn_from_bytes({buffer.data(), buffer.size()}, pad_index);
}

}  // namespace am3d::exe