// SPDX-License-Identifier: GPL-3.0-or-later
#include "front_tim.hpp"
#include <vector>

using namespace am3d;

namespace {

void put16(std::uint8_t* at, unsigned value) {
    at[0] = static_cast<std::uint8_t>(value);
    at[1] = static_cast<std::uint8_t>(value >> 8);
}

void put32(std::uint8_t* at, unsigned value) {
    put16(at, value);
    put16(at + 2, value >> 16);
}

struct UploadCall {
    platform::FrontTimUploadRect rect;
    std::vector<std::uint16_t> words;
};

void collect_upload(void* context, const platform::FrontTimUploadRect& rect,
    const std::uint16_t* words, std::size_t count) {
    auto& calls = *static_cast<std::vector<UploadCall>*>(context);
    calls.push_back({rect, std::vector<std::uint16_t>(words, words + count)});
}

}

int main() {
    // Four pixels, two colors. The low nibble is the left pixel.
    // Color 0 is skipped. Color 1 is white.
    std::uint8_t bytes[8 + 16 + 14] = {};
    put32(bytes + 0, 0x10);
    put32(bytes + 4, 0x8);
    put32(bytes + 8, 16);
    put16(bytes + 12, 0);
    put16(bytes + 14, 0);
    put16(bytes + 16, 2);
    put16(bytes + 18, 1);
    put16(bytes + 20, 0);
    put16(bytes + 22, 0x7fff);
    put32(bytes + 24, 14);
    put16(bytes + 28, 0);
    put16(bytes + 30, 0);
    put16(bytes + 32, 1);
    put16(bytes + 34, 1);
    put16(bytes + 36, 0x0001);

    platform::FillVram vram;
    platform::FrontTim picture;
    if (!platform::paint_front_tim(bytes, sizeof bytes, 10, 20, vram, &picture)) return 1;
    if (picture.width != 4 || picture.height != 1) return 2;
    if (vram.pixel(10, 20) != 0x7fff) return 3;
    if (vram.pixel(11, 20) != 0 || vram.pixel(12, 20) != 0 || vram.pixel(13, 20) != 0) return 4;

    // The upload sends raw words, including bit 15, without decoding pixels.
    put16(bytes + 12, 512);
    put16(bytes + 14, 506);
    put16(bytes + 20, 0x8001);
    put16(bytes + 22, 0xffff);
    put16(bytes + 28, 640);
    put16(bytes + 30, 0);
    put16(bytes + 36, 0x8abc);
    std::vector<UploadCall> calls;
    if (!platform::upload_front_tim(bytes, sizeof bytes, collect_upload, &calls)) return 5;
    if (calls.size() != 2) return 6;
    if (calls[0].rect.x != 512 || calls[0].rect.y != 506 ||
        calls[0].rect.width != 2 || calls[0].rect.height != 1 ||
        calls[0].words != std::vector<std::uint16_t>{0x8001, 0xffff}) return 7;
    if (calls[1].rect.x != 640 || calls[1].rect.y != 0 ||
        calls[1].rect.width != 1 || calls[1].rect.height != 1 ||
        calls[1].words != std::vector<std::uint16_t>{0x8abc}) return 8;

    calls.clear();
    put32(bytes + 24, 13); // Invalid second block must not submit the first.
    if (platform::upload_front_tim(bytes, sizeof bytes, collect_upload, &calls) ||
        !calls.empty()) return 9;
    put32(bytes + 24, 14);
    put16(bytes + 12, 1023); // Valid block length, but the rectangle wraps.
    if (platform::upload_front_tim(bytes, sizeof bytes, collect_upload, &calls) ||
        !calls.empty()) return 10;
    put16(bytes + 12, 512);
    put16(bytes + 34, 0);
    if (platform::upload_front_tim(bytes, sizeof bytes, collect_upload, &calls) ||
        !calls.empty()) return 11;
    put16(bytes + 34, 1);
    put32(bytes + 8, 0xffffffffu);
    if (platform::upload_front_tim(bytes, sizeof bytes, collect_upload, &calls) ||
        !calls.empty()) return 12;
    put32(bytes + 8, 16);
    if (platform::upload_front_tim(bytes, sizeof bytes - 1, collect_upload, &calls) ||
        platform::upload_front_tim(nullptr, sizeof bytes, collect_upload, &calls) ||
        platform::upload_front_tim(bytes, sizeof bytes, nullptr, nullptr) ||
        !calls.empty()) return 13;

    bytes[0] = 0;
    if (platform::paint_front_tim(bytes, sizeof bytes, 0, 0, vram, nullptr)) return 14;
    return 0;
}
