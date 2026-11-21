// SPDX-License-Identifier: GPL-3.0-or-later
#include "menu_submit_frame.hpp"
#include "front_tim.hpp"
#include "call_8007c11c.hpp"
#include "display_fill.hpp"
#include "menu_selection_highlight.hpp"

#include <unordered_set>
#include <vector>

namespace am3d::platform {
namespace {

constexpr std::uint32_t kRetailTable = 0x800c8518u;
constexpr std::uint32_t kRetailCount = 0x900u;
constexpr std::uint32_t kExpectedOtag = 0x800ca914u;
constexpr std::uint32_t kRamBase = 0x800c8000u;
constexpr std::uint32_t kCommandGuest = 0x800cb000u;
constexpr std::size_t kRamWords = 4096u;
constexpr std::uint32_t kTerminator = 0xffffffu;
constexpr std::size_t kMaxNodes = 4096u;
constexpr std::size_t kMaxPayloadWords = 16384u;

static std::uint32_t pack_xy(unsigned x, unsigned y) {
    return x | (y << 16);
}

struct UploadSinkState {
    FillVram* vram = nullptr;
};

static void front_tim_upload_sink(void* context, const FrontTimUploadRect& rect,
                                  const std::uint16_t* words, std::size_t word_count) {
    auto& state = *static_cast<UploadSinkState*>(context);
    for (std::size_t i = 0; i < word_count; ++i) {
        const unsigned x = rect.x + static_cast<unsigned>(i % rect.width);
        const unsigned y = rect.y + static_cast<unsigned>(i / rect.width);
        state.vram->write_pixel(x, y, words[i]);
    }
}

static bool guest_offset(std::uint32_t guest, std::uint32_t* word_index) {
    if (guest < kRamBase || ((guest - kRamBase) & 3u) != 0u) {
        return false;
    }
    const std::uint32_t byte = guest - kRamBase;
    if (byte / 4u >= kRamWords) {
        return false;
    }
    *word_index = byte / 4u;
    return true;
}

static std::uint16_t sample_clut(const FillVram& vram, unsigned clut_x, unsigned clut_y,
                                 unsigned index) {
    return vram.pixel((clut_x & 0x3f0u) + index, clut_y & 0x1ffu);
}

static unsigned texture_index(const FillVram& vram, unsigned tpage_x, unsigned tpage_y,
                              unsigned tx, unsigned ty) {
    const unsigned word_x = tpage_x + tx / 4u;
    const unsigned word_y = tpage_y + ty;
    const std::uint16_t packed = vram.pixel(word_x, word_y);
    const unsigned shift = (tx & 3u) * 4u;
    return (packed >> shift) & 0xfu;
}

static bool run_fill(FillVram& vram, const std::uint32_t* words) {
    const exe::FillPacket packet{
        3u << 24,
        words[0],
        words[1],
        words[2],
    };
    vram.draw_prim(packet);
    return true;
}

static bool run_upload(FillVram& vram, const std::vector<std::uint32_t>& words) {
    if (words.size() < 3u) {
        return false;
    }
    const unsigned x = words[1] & 1023u;
    const unsigned y = (words[1] >> 16) & 511u;
    const unsigned width = words[2] & 0xffffu;
    const unsigned height = (words[2] >> 16) & 0xffffu;
    if (width == 0u || height == 0u || width > 1024u || height > 512u) {
        return false;
    }
    const std::size_t expected =
        3u + (static_cast<std::size_t>(width) * height + 1u) / 2u;
    if (words.size() != expected) {
        return false;
    }
    std::size_t idx = 3u;
    for (unsigned row = 0; row < height; ++row) {
        for (unsigned col = 0; col < width; col += 2u) {
            if (idx >= words.size()) {
                return false;
            }
            const std::uint32_t pair = words[idx++];
            if (col + 1u < width) {
                vram.write_pixel(x + col, y + row, static_cast<std::uint16_t>(pair & 0xffffu));
                vram.write_pixel(x + col + 1u, y + row,
                    static_cast<std::uint16_t>((pair >> 16) & 0xffffu));
            } else {
                vram.write_pixel(x + col, y + row, static_cast<std::uint16_t>(pair & 0xffffu));
            }
        }
    }
    return true;
}

static bool run_textured_quad(FillVram& vram, const std::uint32_t* words) {
    const unsigned x0 = words[1] & 1023u;
    const unsigned y0 = (words[1] >> 16) & 511u;
    const unsigned clut_packed = (words[2] >> 16) & 0xffffu;
    const unsigned clut_x = (clut_packed & 0x3fu) * 16u;
    const unsigned clut_y = (clut_packed >> 6) & 0x1ffu;
    const unsigned x1 = words[3] & 1023u;
    const unsigned y1 = (words[3] >> 16) & 511u;
    const unsigned tpage_x = ((words[4] >> 16) & 0x3ffu) * 64u;
    const unsigned tpage_y = ((words[4] >> 22) & 0x1ffu) * 256u;
    const unsigned x2 = words[5] & 1023u;
    const unsigned y2 = (words[5] >> 16) & 511u;
    const unsigned x3 = words[7] & 1023u;
    const unsigned y3 = (words[7] >> 16) & 511u;
  (void)words[6];

    const unsigned left = x0 < x3 ? x0 : x3;
    const unsigned right = x1 > x2 ? x1 : x2;
    const unsigned top = y0 < y1 ? y0 : y1;
    const unsigned bottom = y2 > y3 ? y2 : y3;
    if (right <= left || bottom <= top) {
        return false;
    }
    for (unsigned py = top; py < bottom; ++py) {
        for (unsigned px = left; px < right; ++px) {
            const unsigned tx = px - x0;
            const unsigned ty = py - y0;
            const unsigned index = texture_index(vram, tpage_x, tpage_y, tx, ty);
            const std::uint16_t color = sample_clut(vram, clut_x, clut_y, index);
            if (color == 0u) {
                continue;
            }
            vram.write_pixel(px, py, color & 0x7fffu);
        }
    }
    return true;
}

static bool run_command(FillVram& vram, const std::vector<std::uint32_t>& words) {
    if (words.empty()) {
        return false;
    }
    switch (words[0] >> 24) {
        case 0x02:
            return words.size() == 3u && run_fill(vram, words.data());
        case 0xa0:
            return run_upload(vram, words);
        case 0x2f:
            return words.size() == 9u && run_textured_quad(vram, words.data());
        default:
            return false;
    }
}

static bool walk_ordering_table(FillVram& vram, const std::vector<std::uint32_t>& ram,
                                std::uint32_t start_byte) {
    if ((start_byte & 3u) != 0u || start_byte / 4u >= ram.size()) {
        return false;
    }
    std::unordered_set<std::uint32_t> seen;
    std::vector<std::uint32_t> stream;
    std::uint32_t link = start_byte;
    while (link != kTerminator) {
        if ((link & 3u) != 0u || link / 4u >= ram.size() ||
            !seen.insert(link).second || seen.size() > kMaxNodes) {
            return false;
        }
        const std::uint32_t tag = ram[link / 4u];
        const std::size_t count = tag >> 24;
        const std::size_t index = link / 4u + 1u;
        if (count > ram.size() - index || count > kMaxPayloadWords - stream.size()) {
            return false;
        }
        stream.insert(stream.end(), ram.begin() + static_cast<std::ptrdiff_t>(index),
            ram.begin() + static_cast<std::ptrdiff_t>(index + count));
        link = tag & 0xffffffu;
    }
    std::vector<std::vector<std::uint32_t>> commands;
    for (std::size_t i = 0; i < stream.size();) {
        std::size_t length = 0;
        switch (stream[i] >> 24) {
            case 0x02:
                length = 3u;
                break;
            case 0x2f:
                length = 9u;
                break;
            case 0xa0: {
                if (stream.size() - i < 3u) {
                    return false;
                }
                const unsigned width = stream[i + 2] & 0xffffu;
                const unsigned height = stream[i + 2] >> 16;
                if (width == 0u || width > 1024u || height == 0u || height > 512u) {
                    return false;
                }
                length = 3u + (static_cast<std::size_t>(width) * height + 1u) / 2u;
                break;
            }
            default:
                return false;
        }
        if (length > stream.size() - i) {
            return false;
        }
        commands.emplace_back(stream.begin() + static_cast<std::ptrdiff_t>(i),
            stream.begin() + static_cast<std::ptrdiff_t>(i + length));
        i += length;
    }
    for (const auto& command : commands) {
        if (!run_command(vram, command)) {
            return false;
        }
    }
    return true;
}

class SubmitBridge final : public exe::SubmitOrderingTableGpu {
public:
    SubmitBridge(FillVram& vram, std::vector<std::uint32_t>& ram, MenuSubmitFrameTrace& trace)
        : vram_(vram), ram_(ram), trace_(trace) {}

    void draw_sync(std::uint32_t mode) override {
        if (mode == 0u) {
            ++trace_.draw_sync_calls;
        }
        vram_.draw_sync(static_cast<int>(mode));
    }

    void draw_sync_callback(std::uint32_t) override {}

    std::uint32_t draw_otag(std::uint32_t address) override {
        trace_.draw_otag_address = address;
        if (address < kRamBase || ((address - kRamBase) & 3u) != 0u) {
            trace_.list_accepted = false;
            return 0u;
        }
        const std::uint32_t start_byte = address - kRamBase;
        if (start_byte / 4u >= ram_.size()) {
            trace_.list_accepted = false;
            return 0u;
        }
        trace_.list_accepted = walk_ordering_table(vram_, ram_, start_byte);
        return trace_.list_accepted ? 1u : 0u;
    }

private:
    FillVram& vram_;
    std::vector<std::uint32_t>& ram_;
    MenuSubmitFrameTrace& trace_;
};

static void fill_ordering_table(std::vector<std::uint32_t>& ram, unsigned quad_x,
                                unsigned quad_y) {
    ram.assign(kRamWords, 0u);
    const auto byte_off = [](std::uint32_t guest) { return guest - kRamBase; };
    const std::uint32_t cmd_off = byte_off(kCommandGuest);
    ram[cmd_off / 4u] = (12u << 24) | kTerminator;
    const unsigned clut = (512u / 16u) | (506u << 6u);
    const unsigned tpage = 640u / 64u;
    const std::uint32_t commands[] = {
        0x02202020u,
        pack_xy(0u, 0u),
        pack_xy(320u, 240u),
        0x2f808080u,
        pack_xy(quad_x, quad_y),
        clut << 16,
        pack_xy(quad_x + 44u, quad_y),
        44u | (tpage << 16),
        pack_xy(quad_x, quad_y + 128u),
        128u << 8,
        pack_xy(quad_x + 44u, quad_y + 128u),
        44u | (128u << 8),
    };
    for (std::size_t i = 0; i < sizeof commands / sizeof commands[0]; ++i) {
        ram[cmd_off / 4u + 1u + i] = commands[i];
    }
    for (std::uint32_t i = 0; i + 3u < kRetailCount; ++i) {
        const std::uint32_t entry = kRetailTable + i * 4u;
        std::uint32_t word_index = 0;
        if (!guest_offset(entry, &word_index)) {
            continue;
        }
        const std::uint32_t next = kRetailTable + (i + 1u) * 4u;
        ram[word_index] = (0u << 24) | (byte_off(next) & 0xffffffu);
    }
    const std::uint32_t tail0 = kRetailTable + (kRetailCount - 3u) * 4u;
    const std::uint32_t tail1 = kRetailTable + (kRetailCount - 2u) * 4u;
    const std::uint32_t tail2 = kRetailTable + (kRetailCount - 1u) * 4u;
    std::uint32_t word_index = 0;
    if (guest_offset(tail0, &word_index)) {
        ram[word_index] = (0u << 24) | (cmd_off & 0xffffffu);
    }
    if (guest_offset(tail1, &word_index)) {
        ram[word_index] = (0u << 24) | (byte_off(tail0) & 0xffffffu);
    }
    if (guest_offset(tail2, &word_index)) {
        ram[word_index] = (0u << 24) | (byte_off(tail1) & 0xffffffu);
    }
}

static void draw_marker(const MenuSubmitFrameRequest& request, FillVram& vram) {
    const exe::DisplayFillState state{
        request.origin_x,
        request.origin_y,
        static_cast<std::uint16_t>(request.marker_x),
        static_cast<std::uint16_t>(request.marker_y),
        static_cast<std::uint16_t>(request.marker_x + 16u),
        static_cast<std::uint16_t>(request.marker_y + 16u),
    };
    exe::fill_display(request.marker_color, state, vram);
}

}  // namespace

MenuSubmitFrameTrace menu_submit_frame(const MenuSubmitFrameRequest& request, FillVram& vram) {
    MenuSubmitFrameTrace trace{};
    std::vector<std::uint32_t> ram;
    const unsigned quad_x = request.origin_x + request.quad_x;
    const unsigned quad_y = request.origin_y + request.quad_y;
    fill_ordering_table(ram, quad_x, quad_y);

    if (request.front_bytes != nullptr && request.front_size != 0u) {
        UploadSinkState upload{&vram};
        (void)upload_front_tim(request.front_bytes, request.front_size, front_tim_upload_sink,
            &upload);
    }

    SubmitBridge bridge(vram, ram, trace);
    const auto read_flag = [] { return 0u; };
    trace.submit_return =
        exe::call_8007c11c(kRetailTable, kRetailCount, read_flag, bridge);
    draw_marker(request, vram);
    draw_menu_selection_highlight(vram, request.origin_x, request.origin_y, request.quad_x,
        request.quad_y, request.selection_highlight_index);
    return trace;
}

}  // namespace am3d::platform