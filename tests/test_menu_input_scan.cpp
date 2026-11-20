// SPDX-License-Identifier: GPL-3.0-or-later
#include "menu_input_scan.hpp"

#include <array>
#include <cstdint>

namespace {

std::uint32_t g_state = 0u;

std::uint32_t pad_get_state(std::uint32_t port) {
    (void)port;
    return g_state;
}

constexpr std::array<std::uint8_t, 4u> kReleased{0u, 0x41u, 0xffu, 0xffu};
constexpr std::array<std::uint8_t, 4u> kUp{0u, 0x41u, 0xefu, 0xffu};
constexpr std::array<std::uint8_t, 4u> kHeld{0u, 0x41u, 0xbfu, 0xffu};

}

int main() {
    std::array<std::uint8_t, 0x100u> bytes{};
    std::uint8_t* record = bytes.data();
    am3d::exe::MenuInputScanState scan{};
    std::uint32_t table_index = 0u;
    std::uint32_t sp20 = 0u;
    std::uint32_t sp18 = 1u;
    std::uint32_t stack_word_1c = 4u;
    g_state = 2u;
    am3d::exe::MenuInputScanStep up = am3d::exe::menu_input_scan_step(
        sp18, 2u, pad_get_state, kUp.data(), table_index, kUp.size(), sp20, 0u,
        0u, record, 0u, scan, stack_word_1c);
    if (!up.tail_ran || !up.loop_again || bytes[0x0bu] != 0x80u) {
        return 1;
    }

    bytes.fill(0u);
    record = bytes.data();
    scan = {};
    table_index = 0u;
    sp20 = 0u;
    sp18 = 0u;
    stack_word_1c = 8u;
    am3d::exe::MenuInputScanStep clear = am3d::exe::menu_input_scan_step(
        sp18, 0u, pad_get_state, kReleased.data(), table_index, kReleased.size(),
        sp20, 0u, 0u, record, 0u, scan, stack_word_1c);
    if (!clear.tail_ran || !clear.loop_again || bytes[0x0bu] != 0u) {
        return 2;
    }

    bytes.fill(0x11u);
    record = bytes.data();
    scan = {};
    table_index = 0u;
    sp18 = 0u;
    am3d::exe::MenuInputScanStep held = am3d::exe::menu_input_scan_step(
        sp18, 0u, pad_get_state, kHeld.data(), table_index, kHeld.size(), sp20,
        0u, 0u, record, 0u, scan, stack_word_1c);
    if (!held.tail_ran || !held.loop_again || bytes[0x0bu] != 0x7fu ||
        record != bytes.data() + 0x7cu) {
        return 3;
    }

    g_state = 7u;
    table_index = 0u;
    sp18 = 0u;
    am3d::exe::MenuInputScanStep high = am3d::exe::menu_input_scan_step(
        sp18, 0u, pad_get_state, kReleased.data(), table_index, kReleased.size(),
        sp20, 0u, 0u, record, 0u, scan, stack_word_1c);
    if (high.tail_ran) {
        return 4;
    }

    bytes.fill(0u);
    record = bytes.data();
    scan = {};
    table_index = 0u;
    sp20 = 0u;
    g_state = 2u;
    constexpr std::uint32_t kForceS6 = 1u;
    constexpr std::array<std::uint8_t, 4u> kUpS6{0u, 0x41u, 0x6fu, 0xffu};
    sp18 = 1u;
    stack_word_1c = 4u;
    am3d::exe::MenuInputScanStep s6_up = am3d::exe::menu_input_scan_step(
        sp18, 2u, pad_get_state, kUpS6.data(), table_index, kUpS6.size(), sp20,
        0u, 0u, record, 0u, scan, stack_word_1c, &kForceS6);
    if (!s6_up.tail_ran || !s6_up.loop_again || bytes[0x0au] != 0x80u ||
        bytes[0x0bu] != 0x80u) {
        return 5;
    }

    bytes.fill(0u);
    record = bytes.data();
    scan = {};
    table_index = 0u;
    sp20 = 0u;
    constexpr std::array<std::uint8_t, 4u> kS6Released{0u, 0x41u, 0xffu, 0xffu};
    sp18 = 0u;
    stack_word_1c = 8u;
    am3d::exe::MenuInputScanStep s6_clear = am3d::exe::menu_input_scan_step(
        sp18, 0u, pad_get_state, kS6Released.data(), table_index,
        kS6Released.size(), sp20,
        0u, 0u, record, 0u, scan, stack_word_1c, &kForceS6);
    if (!s6_clear.tail_ran || !s6_clear.loop_again || bytes[0x0au] != 0u ||
        bytes[0x0bu] != 0u) {
        return 6;
    }

    bytes.fill(0u);
    record = bytes.data();
    scan = {};
    table_index = 0u;
    sp20 = 0u;
    g_state = 2u;
    constexpr std::uint32_t kCompareFour = 4u;
    std::uint32_t sp28 = 0u;
    sp18 = 1u;
    am3d::exe::MenuInputScanStep alt = am3d::exe::menu_input_scan_step(
        sp18, 2u, pad_get_state, kReleased.data(), table_index, kReleased.size(),
        sp20, 0u, kCompareFour, record, 0u, scan, stack_word_1c, nullptr, &sp28);
    if (!alt.tail_ran || !alt.loop_again || !alt.compare_four_ran ||
        !alt.compare_four_to_65168 || alt.compare_four_v0 != 1u ||
        table_index != 4u || record != bytes.data() + 0x7cu ||
        scan.s7 != 1u || scan.table_cursor != 4u || sp28 != 4u) {
        return 7;
    }

    bytes.fill(0u);
    record = bytes.data();
    scan = {};
    table_index = 0u;
    sp20 = 0u;
    g_state = 3u;
    constexpr std::uint32_t kProvisionalDownDest = 0x80064f14u;
    am3d::exe::PadStateDispatchInject pad_inject{};
    pad_inject.entry[3] = &kProvisionalDownDest;
    sp18 = 0u;
    am3d::exe::MenuInputScanStep down = am3d::exe::menu_input_scan_step(
        sp18, 0u, pad_get_state, kReleased.data(), table_index, kReleased.size(),
        sp20, 0u, 0u, record, 0u, scan, stack_word_1c, nullptr, nullptr, &pad_inject);
    if (!down.dispatch.destination_stated ||
        down.dispatch.destination != kProvisionalDownDest ||
        down.dispatch.word_address != 0x800c3ea4u || !down.tail_ran ||
        !down.loop_again) {
        return 8;
    }

    g_state = 3u;
    am3d::exe::MenuInputScanStep down_no_inject = am3d::exe::menu_input_scan_step(
        sp18, 0u, pad_get_state, kReleased.data(), table_index, kReleased.size(),
        sp20, 0u, 0u, record, 0u, scan, stack_word_1c);
    if (down_no_inject.dispatch.destination_stated || down_no_inject.tail_ran) {
        return 9;
    }

    am3d::exe::MenuInputScanStep step{};
    am3d::exe::MenuInputScanState reentry_scan{};
    reentry_scan.index = 4u;
    am3d::exe::record_65194_reentry_from_64e0c(step, reentry_scan);
    if (!step.reentered_65194 || !step.loop_reentry_65194_recorded ||
        !step.loop_reentry_65194.branch_to_651c8 ||
        step.loop_reentry_65194.v0 != 0x800e0000u) {
        return 10;
    }

    am3d::exe::MenuInputScanState zero_index{};
    step = {};
    am3d::exe::record_65194_reentry_from_64e0c(step, zero_index);
    if (!step.reentered_65194 || step.loop_reentry_65194_recorded) {
        return 11;
    }

    return 0;
}