// SPDX-License-Identifier: GPL-3.0-or-later
#include "alp1_pad_spawn.hpp"

#include "mission_movement_slice.hpp"

#include <cstdint>
#include <fstream>
#include <vector>

namespace am3d::exe {
namespace {

constexpr std::size_t kAlp1PadHeaderBytes = 0x20u;
constexpr std::size_t kAlp1PadRecordStride = 0x10u;

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
    std::ifstream in(resolved, std::ios::binary);
    if (!in) {
        return {};
    }
    in.seekg(0, std::ios::end);
    const auto end = in.tellg();
    if (end <= 0) {
        return {};
    }
    std::vector<std::uint8_t> buffer(static_cast<std::size_t>(end));
    in.seekg(0, std::ios::beg);
    if (!in.read(reinterpret_cast<char*>(buffer.data()),
                 static_cast<std::streamsize>(buffer.size()))) {
        return {};
    }
    return parse_alp1_pad_spawn_from_bytes({buffer.data(), buffer.size()}, pad_index);
}

}  // namespace am3d::exe