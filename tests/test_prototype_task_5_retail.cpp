// SPDX-License-Identifier: GPL-3.0-or-later
#include "front_tim.hpp"

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <vector>

namespace {

constexpr int kSkipNoDisc = 77;

std::uint16_t read_u16(const std::uint8_t* bytes, std::size_t at) {
    return static_cast<std::uint16_t>(bytes[at] | (static_cast<unsigned>(bytes[at + 1]) << 8));
}

std::uint32_t read_u32(const std::uint8_t* bytes, std::size_t at) {
    return bytes[at] | (static_cast<unsigned>(bytes[at + 1]) << 8) |
        (static_cast<unsigned>(bytes[at + 2]) << 16) |
        (static_cast<unsigned>(bytes[at + 3]) << 24);
}

std::filesystem::path resolve_front_tim() {
    const std::filesystem::path from_build = "disc/DATA/FRONT.TIM";
    if (std::filesystem::is_regular_file(from_build)) {
        return from_build;
    }
    const std::filesystem::path from_root = "build/disc/DATA/FRONT.TIM";
    if (std::filesystem::is_regular_file(from_root)) {
        return from_root;
    }
    return {};
}

bool load_front_bytes(const std::filesystem::path& path, std::vector<std::uint8_t>& out) {
    std::ifstream in(path, std::ios::binary);
    if (!in) {
        return false;
    }
    out.assign(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
    return static_cast<bool>(in);
}

struct UploadCall {
    am3d::platform::FrontTimUploadRect rect;
    std::size_t word_count = 0;
};

void collect_upload(void* context, const am3d::platform::FrontTimUploadRect& rect,
    const std::uint16_t* words, std::size_t count) {
    auto& calls = *static_cast<std::vector<UploadCall>*>(context);
    calls.push_back({rect, count});
    (void)words;
}

bool layout_matches_front_tim_md(const std::uint8_t* bytes, std::size_t size) {
    if (size != 2880u) {
        return false;
    }
    if (read_u32(bytes, 0) != 0x10u || read_u32(bytes, 4) != 0x8u) {
        return false;
    }
    if (read_u32(bytes, 8) != 0x2cu) {
        return false;
    }
    if (read_u16(bytes, 12) != 512u || read_u16(bytes, 14) != 506u ||
        read_u16(bytes, 16) != 16u || read_u16(bytes, 18) != 1u) {
        return false;
    }
    if (read_u16(bytes, 20) != 0x5335u) {
        return false;
    }
    if (read_u32(bytes, 52) != 0x0b0cu) {
        return false;
    }
    if (read_u16(bytes, 56) != 640u || read_u16(bytes, 58) != 0u ||
        read_u16(bytes, 60) != 11u || read_u16(bytes, 62) != 128u) {
        return false;
    }
    return true;
}

bool painted_picture_has_pixel(const am3d::platform::FillVram& vram) {
    constexpr unsigned origin_x = 234u;
    constexpr unsigned origin_y = 56u;
    for (unsigned y = origin_y; y < origin_y + 128u; ++y) {
        for (unsigned x = origin_x; x < origin_x + 44u; ++x) {
            if (vram.pixel(x, y) != 0u) {
                return true;
            }
        }
    }
    return false;
}

}  // namespace

// PROTOTYPE.md row 5 disc-backed acceptance when build/disc/DATA/FRONT.TIM exists.
// Field layout cites docs/research/re/front-tim.md.
int main() {
    const std::filesystem::path front_path = resolve_front_tim();
    if (front_path.empty()) {
        return kSkipNoDisc;
    }

    std::vector<std::uint8_t> front_bytes;
    if (!load_front_bytes(front_path, front_bytes) || front_bytes.empty()) {
        return kSkipNoDisc;
    }

    if (!layout_matches_front_tim_md(front_bytes.data(), front_bytes.size())) {
        return 1;
    }

    std::vector<UploadCall> calls;
    if (!am3d::platform::upload_front_tim(front_bytes.data(), front_bytes.size(), collect_upload,
            &calls)) {
        return 2;
    }
    if (calls.size() != 2u) {
        return 3;
    }
    if (calls[0].rect.x != 512u || calls[0].rect.y != 506u || calls[0].rect.width != 16u ||
        calls[0].rect.height != 1u || calls[0].word_count != 16u) {
        return 4;
    }
    if (calls[1].rect.x != 640u || calls[1].rect.y != 0u || calls[1].rect.width != 11u ||
        calls[1].rect.height != 128u || calls[1].word_count != 1408u) {
        return 5;
    }

    am3d::platform::FillVram vram;
    am3d::platform::FrontTim picture{};
    if (!am3d::platform::paint_front_tim(front_bytes.data(), front_bytes.size(), 234u, 56u, vram,
            &picture)) {
        return 6;
    }
    if (picture.width != 44u || picture.height != 128u) {
        return 7;
    }
    if (!painted_picture_has_pixel(vram)) {
        return 8;
    }

    return 0;
}