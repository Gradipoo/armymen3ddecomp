// SPDX-License-Identifier: GPL-3.0-or-later
#include "prototype_playable_pipeline.hpp"

#include "alp1_pad_spawn_fixture.hpp"
#include "disc_data_file_read.hpp"
#include "prototype_task_7_menu.hpp"
#include "prototype_task_8_mission.hpp"

#include <array>
#include <vector>

namespace am3d::exe {
namespace {

constexpr std::size_t kFrontTimMeasuredBytes = 2880u;

std::vector<std::uint8_t> load_front_tim_disc_bytes(const std::filesystem::path& disc_root) {
    std::vector<std::uint8_t> bytes;
    if (disc_root.empty()) {
        return bytes;
    }
    std::array<std::uint8_t, kFrontTimMeasuredBytes> buffer{};
    const platform::DiscDataFileReadResult read = platform::read_disc_data_file(
        disc_root / "DATA/FRONT.TIM", buffer.size(), buffer.data());
    if (!read.ok || read.truncated || read.bytes_read != kFrontTimMeasuredBytes) {
        return bytes;
    }
    bytes.assign(buffer.begin(), buffer.begin() + read.bytes_read);
    return bytes;
}

}  // namespace

PrototypePlayablePipelineConfig::PrototypePlayablePipelineConfig() {
    movement_start = mission_start_from_alp1_pad_fixture();
}

PrototypePlayablePipelineResult run_prototype_playable_pipeline(
    const PrototypePlayablePipelineConfig& config,
    std::uint32_t (*pad_get_state)(std::uint32_t port)) {
    PrototypePlayablePipelineResult out{};
    if (pad_get_state == nullptr) {
        return out;
    }

    const std::vector<std::uint8_t> front_bytes = load_front_tim_disc_bytes(config.disc_root);
    const std::uint8_t* front_ptr =
        front_bytes.empty() ? nullptr : front_bytes.data();
    const std::size_t front_size = front_bytes.size();

    // Row 7 owns the scan. Its pad returns 2 until s7 reaches 8, then 3, so the
    // Down step still dispatches when callers pass an idle pad.
    const PrototypeTask7MenuResult menu = run_prototype_task_7_menu_transition(
        prototype_task_7_pad_get_state, front_ptr, front_size);
    out.frames.menu = menu.frames_run;
    out.frames.down = menu.frames_run_b;
    out.menu_s7_after_menu_budget = menu.s7_after_a;
    out.menu_s7 = menu.s7_after_b;
    out.dispatch_destination_stated = menu.destination_stated;
    out.dispatch_tail_ran = menu.phase_b_tail_ran;
    out.dispatch_destination = menu.destination;
    out.dispatch_word_address = menu.word_address;
    out.menu_marker_x_a = menu.marker_x_a;
    out.menu_marker_x_b = menu.marker_x_b;
    out.menu_selection_after_a = menu.selection_index_after_a;
    out.menu_selection_after_b = menu.selection_index_after_b;
    out.has_front = menu.has_front;

    const PrototypeTask8MissionResult mission =
        run_prototype_task_8_mission_slice(config.disc_root);
    out.frames.mission = mission.frames_run;
    out.mission_path_gpr = mission.mission_path_gpr;
    out.movement_final_state = mission.final_state;
    out.spawn_from_pad = mission.spawn_from_pad;
    return out;
}

}  // namespace am3d::exe
