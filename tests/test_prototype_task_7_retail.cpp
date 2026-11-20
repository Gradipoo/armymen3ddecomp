// SPDX-License-Identifier: GPL-3.0-or-later
#include "menu_input_scan_loop.hpp"
#include "menu_submit_frame.hpp"
#include "menu_table_sequence.hpp"

#include <array>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <vector>

namespace {

constexpr int kSkipNoDisc = 77;

am3d::exe::MenuInputScanState* g_scan_for_pad = nullptr;

std::uint32_t pad_get_state_retail(std::uint32_t port) {
    (void)port;
    if (g_scan_for_pad != nullptr && g_scan_for_pad->s7 >= 8u) {
        return 3u;
    }
    return 2u;
}

constexpr std::size_t kSlots = 8u;

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

bool front_stand_in_has_visible_pixel(const am3d::platform::FillVram& vram,
                                      std::uint16_t origin_x, std::uint16_t origin_y) {
    const unsigned left = origin_x + 234u;
    const unsigned top = origin_y + 56u;
    for (unsigned y = top; y < top + 128u; ++y) {
        for (unsigned x = left; x < left + 44u; ++x) {
            if (vram.pixel(x, y) != 0u) {
                return true;
            }
        }
    }
    return false;
}

int submit_menu_frame(am3d::platform::FillVram& vram, const std::vector<std::uint8_t>& front_bytes,
                      std::uint32_t marker_x, std::uint32_t phase_code) {
    am3d::platform::MenuSubmitFrameRequest request{};
    request.origin_x = 0u;
    request.origin_y = 0u;
    request.marker_x = marker_x;
    request.marker_y = 112u;
    request.marker_color = 0x00ff00u;
    if (!front_bytes.empty()) {
        request.front_bytes = front_bytes.data();
        request.front_size = front_bytes.size();
    }
    const auto trace = am3d::platform::menu_submit_frame(request, vram);
    if (trace.submit_return != 1u) {
        return phase_code + 0;
    }
    if ((vram.argb(marker_x, 112u) & 0xffffffu) != 0x00ff00u) {
        return phase_code + 1;
    }
    if (!front_stand_in_has_visible_pixel(vram, request.origin_x, request.origin_y)) {
        return phase_code + 2;
    }
    return 0;
}

}  // namespace

// PROTOTYPE.md row 7 disc-backed acceptance when build/disc/DATA/FRONT.TIM exists.
int main() {
    const std::filesystem::path front_path = resolve_front_tim();
    if (front_path.empty()) {
        return kSkipNoDisc;
    }

    std::vector<std::uint8_t> front_bytes;
    if (!load_front_bytes(front_path, front_bytes) || front_bytes.empty()) {
        return kSkipNoDisc;
    }

    std::array<std::uint8_t, kSlots * am3d::exe::kMenuInputScanSlotBytes> table{};
    am3d::exe::menu_table_fill_released_slots(table.data(), kSlots);

    std::array<std::uint8_t, 0x400u> bytes{};
    std::uint8_t* record = bytes.data();
    am3d::exe::MenuInputScanState scan{};
    am3d::exe::MenuInputScanIndices indices{};
    indices.stack_word_18 = 0u;
    indices.menu_table_bytes = static_cast<std::uint32_t>(table.size());
    std::uint32_t sp20 = 0u;
    std::uint32_t stack_word_1c = 4u;
    am3d::exe::MenuTableSequencer sequencer{};

    g_scan_for_pad = &scan;
    const am3d::exe::MenuInputScanLoopResult phase_a = am3d::exe::run_menu_input_scan_frames(
        4u, pad_get_state_retail, table.data(), indices, sp20, 0u, 0u, record, scan, stack_word_1c,
        &sequencer, nullptr);
    if (phase_a.frames_run != 4u) {
        return 1;
    }
    if (scan.s7 != 8u) {
        return 2;
    }
    if (bytes[0x0bu] != 0u || bytes[0x87u] != 0x80u) {
        return 3;
    }
    if (!phase_a.last_step.tail_ran) {
        return 4;
    }

    const std::uint32_t marker_a = 200u + scan.s7 * 12u;
    am3d::platform::FillVram vram_a;
    const int submit_a = submit_menu_frame(vram_a, front_bytes, marker_a, 20);
    if (submit_a != 0) {
        return submit_a;
    }

    constexpr std::uint32_t kProvisionalDownDest = 0x80064f14u;
    am3d::exe::PadStateDispatchInject pad_inject{};
    pad_inject.entry[3] = &kProvisionalDownDest;

    am3d::exe::menu_input_scan_host_resume(scan, indices, stack_word_1c, scan.s7 + 1u);
    const std::uint32_t s7_before_transition = scan.s7;
    const am3d::exe::MenuInputScanLoopResult transition = am3d::exe::run_menu_input_scan_frames(
        1u, pad_get_state_retail, table.data(), indices, sp20, 0u, 0u, record, scan, stack_word_1c,
        nullptr, nullptr, &pad_inject);
    if (transition.frames_run != 1u) {
        return 30;
    }
    const auto& dispatch = transition.last_step.dispatch;
    if (!dispatch.destination_stated || dispatch.destination != kProvisionalDownDest ||
        dispatch.word_address != 0x800c3ea4u) {
        return 31;
    }
    if (!transition.last_step.tail_ran) {
        return 32;
    }
    if (scan.s7 != s7_before_transition + 1u) {
        return 33;
    }

    const std::uint32_t marker_b = 200u + scan.s7 * 12u;
    am3d::platform::FillVram vram_b;
    const int submit_b = submit_menu_frame(vram_b, front_bytes, marker_b, 40);
    if (submit_b != 0) {
        return submit_b;
    }

    return 0;
}