// SPDX-License-Identifier: GPL-3.0-or-later
#include "prototype_playable_pipeline.hpp"

#include "alp1_pad_spawn_fixture.hpp"
#include "menu_input_scan_loop.hpp"
#include "menu_table_sequence.hpp"
#include "mission_menu_handoff.hpp"

#include <array>
#include <cstdint>

namespace am3d::exe {

namespace {

constexpr std::size_t kSlots = 8u;
constexpr std::uint32_t kProvisionalDownDest = 0x80064f14u;

std::uint32_t down_pad_get_state(std::uint32_t port) {
    (void)port;
    return 3u;
}

}  // namespace

PrototypePlayablePipelineConfig::PrototypePlayablePipelineConfig() {
    movement_start = mission_start_from_alp1_pad_fixture();
}

MissionPadScript prototype_playable_default_mission_script(std::uint32_t frame_budget) {
    MissionPadScript script{};
    const std::uint32_t frames = frame_budget > MissionPadScript::kMaxFrames
                                     ? static_cast<std::uint32_t>(MissionPadScript::kMaxFrames)
                                     : frame_budget;
    script.length = frames;
    const std::size_t idle = static_cast<std::size_t>(frames / 2u);
    for (std::size_t i = 0u; i < script.length; ++i) {
        script.s2[i] =
            i < idle ? MissionPadScript::kPadIdleS2 : MissionPadScript::kPadCrossS2;
    }
    return script;
}

PrototypePlayablePipelineResult run_prototype_playable_pipeline(
    const PrototypePlayablePipelineConfig& config,
    std::uint32_t (*pad_get_state)(std::uint32_t port)) {
    PrototypePlayablePipelineResult out{};

    std::array<std::uint8_t, kSlots * kMenuInputScanSlotBytes> table{};
    menu_table_fill_released_slots(table.data(), kSlots);

    std::array<std::uint8_t, 0x400u> record_bytes{};
    std::uint8_t* record = record_bytes.data();
    MenuInputScanState scan{};
    MenuInputScanIndices indices{};
    indices.stack_word_18 = 0u;
    indices.menu_table_bytes = static_cast<std::uint32_t>(table.size());
    std::uint32_t sp20 = 0u;
    std::uint32_t stack_word_1c = 4u;
    MenuTableSequencer sequencer{};

    const MenuInputScanLoopResult menu_pass = run_menu_input_scan_frames(
        config.menu_frame_budget, pad_get_state, table.data(), indices, sp20, 0u, 0u, record,
        scan, stack_word_1c, &sequencer, nullptr, nullptr);
    out.frames.menu = menu_pass.frames_run;
    out.menu_s7_after_menu_budget = scan.s7;
    out.menu_s7 = scan.s7;

    if (config.down_frame_budget > 0u) {
        PadStateDispatchInject pad_inject{};
        pad_inject.entry[3] = &kProvisionalDownDest;
        menu_input_scan_host_resume(scan, indices, stack_word_1c, scan.s7 + 1u);
        const MenuInputScanLoopResult down_pass = run_menu_input_scan_frames(
            config.down_frame_budget, down_pad_get_state, table.data(), indices, sp20, 0u, 0u,
            record, scan, stack_word_1c, nullptr, nullptr, &pad_inject);
        out.frames.down = down_pass.frames_run;
        out.menu_s7 = scan.s7;
        const auto& dispatch = down_pass.last_step.dispatch;
        out.dispatch_destination_stated = dispatch.destination_stated;
        out.dispatch_tail_ran = down_pass.last_step.tail_ran;
        out.dispatch_destination = dispatch.destination;
        out.dispatch_word_address = dispatch.word_address;
    }

    const MissionLoadIntent intent = record_mission_load_intent();
    out.mission_path_gpr = intent.mission_path_gpr;

    const MissionPadScript script = prototype_playable_default_mission_script(config.mission_frame_budget);
    MissionMovementStartState movement = config.movement_start;
    const MissionMovementRunResult movement_pass =
        run_mission_movement_frames(script, config.movement_start, movement);
    out.frames.mission = movement_pass.frames_run;
    out.movement_final_state = movement_pass.final_state;

    return out;
}

}  // namespace am3d::exe